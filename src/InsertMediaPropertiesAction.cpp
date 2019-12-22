////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (https://ultraschall.fm)
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "CustomActionFactory.h"
#include "FileManager.h"
#include "ITagWriter.h"
#include "InsertMediaPropertiesAction.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "TagWriterFactory.h"
#include "TimeUtilities.h"
#include "FileDialog.h"
#include "NotificationStore.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<InsertMediaPropertiesAction> action;

ServiceStatus InsertMediaPropertiesAction::Execute()
{
    PRECONDITION_RETURN(HasValidProject() == true, SERVICE_FAILURE);

    PRECONDITION_RETURN(ConfigureTargets() == true, SERVICE_FAILURE);
    PRECONDITION_RETURN(ConfigureSources() == true, SERVICE_FAILURE);

    // caution! requires ConfigureSources() to be called beforehand
    PRECONDITION_RETURN(AreChapterMarkersValid(chapterMarkers_) == true, SERVICE_FAILURE);

    ServiceStatus     status = SERVICE_FAILURE;
    NotificationStore supervisor;
    size_t            errorCount = 0;

    for(size_t i = 0; i < targets_.size(); i++)
    {
        ITagWriter* pTagWriter = TagWriterFactory::Create(targets_[i]);
        if(pTagWriter != 0)
        {
            if(pTagWriter->Start(targets_[i]) == true)
            {
                bool commit = false;

                if(pTagWriter->InsertProperties(targets_[i], mediaData_) == true)
                {
                    if(pTagWriter->InsertCoverImage(targets_[i], coverImage_) == true)
                    {
                        if(pTagWriter->InsertChapterMarkers(targets_[i], chapterMarkers_) == true)
                        {
                            commit = true;
                        }
                        else
                        {
                            UnicodeStringStream os;
                            os << "Failed to insert chapter markers into " << targets_[i] << ".";
                            supervisor.RegisterError(os.str());
                            errorCount++;
                        }
                    }
                    else
                    {
                        UnicodeStringStream os;
                        os << "Failed to insert cover image into " << targets_[i] << ".";
                        supervisor.RegisterError(os.str());
                        errorCount++;
                    }
                }
                else
                {
                    UnicodeStringStream os;
                    os << "Failed to insert tags into " << targets_[i] << ".";
                    supervisor.RegisterError(os.str());
                    errorCount++;
                }

                pTagWriter->Stop(commit);
            }

            SafeRelease(pTagWriter);
        }
    }

    if(0 == errorCount)
    {
        for(size_t i = 0; i < targets_.size(); i++)
        {
            UnicodeStringStream os;
            os << targets_[i] << " has been updated successfully.";
            supervisor.RegisterSuccess(os.str());
        }

        status = SERVICE_SUCCESS;
    }

    return status;
}

bool InsertMediaPropertiesAction::ConfigureSources()
{
    bool              result = false;
    NotificationStore supervisor;

    mediaData_.clear();
    coverImage_.clear();
    chapterMarkers_.clear();

    mediaData_ = ReaperProject::Current().ParseNotes();
    if(mediaData_.empty() == true)
    {
        supervisor.RegisterWarning("ID3v2 tags have not been defined yet.");
    }

    coverImage_ = FindCoverImage();
    if(coverImage_.empty() == true)
    {
        supervisor.RegisterWarning("Cover image is missing.");
    }

    chapterMarkers_ = CurrentProject().AllMarkers();
    if(chapterMarkers_.empty() == false)
    {
        bool errorFound = false;
        std::for_each(chapterMarkers_.begin(), chapterMarkers_.end(), [&](const Marker& chapterMarker) {
            if(chapterMarker.Name().length() > Globals::MAX_CHAPTER_TITLE_LENGTH)
            {
                UnicodeStringStream os;
                os << "The chapter marker title '" << chapterMarker.Name() << "' is too long. "
                   << "Make sure that is does not exceed " << Globals::MAX_CHAPTER_TITLE_LENGTH << " characters.";
                supervisor.RegisterError(os.str());
                errorFound = true;
            }
        });

        result = (false == errorFound);
    }
    else
    {
        supervisor.RegisterWarning("No chapters have been set.");
    }

    return result;
} // namespace reaper

bool InsertMediaPropertiesAction::ConfigureTargets()
{
    NotificationStore supervisor;

    targets_.clear();

    static const UnicodeStringArray fileExtensions = {".mp3"};
    for(size_t i = 0; i < fileExtensions.size(); i++)
    {
        UnicodeString targetName = CreateProjectPath(fileExtensions[i]);
        if(FileManager::FileExists(targetName) != false)
        {
            targets_.push_back(targetName);
        }
    }

    if(targets_.empty() == true)
    {
        FileDialog          fileDialog("Select audio file");
        const UnicodeString target = fileDialog.SelectAudioFile();
        if(target.empty() == false)
        {
            targets_.push_back(target);
        }
    }

    return targets_.empty() == false;
}

UnicodeString InsertMediaPropertiesAction::FindCoverImage()
{
    UnicodeString coverImage;

    UnicodeStringArray       files;
    const UnicodeStringArray extensions{".jpg", ".jpeg", ".png"};
    for(size_t i = 0; i < extensions.size(); i++)
    {
        files.push_back(FileManager::AppendPath(CurrentProjectDirectory(), "cover") + extensions[i]);
        files.push_back(FileManager::AppendPath(CurrentProjectDirectory(), "Cover") + extensions[i]);
        files.push_back(FileManager::AppendPath(CurrentProjectDirectory(), "COVER") + extensions[i]);
        files.push_back(FileManager::AppendPath(CurrentProjectDirectory(), CurrentProjectName()) + extensions[i]);
    }

    const size_t imageIndex = FileManager::FileExists(files);
    if(imageIndex != -1)
    {
        coverImage = files[imageIndex];
    }

    return coverImage;
}

}} // namespace ultraschall::reaper
