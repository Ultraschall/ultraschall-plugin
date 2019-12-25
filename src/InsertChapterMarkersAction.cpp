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

#include "InsertChapterMarkersAction.h"
#include "CustomActionFactory.h"
#include "FileManager.h"
#include "StringUtilities.h"
#include "FileDialog.h"
#include "NotificationStore.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<InsertChapterMarkersAction> action;

ServiceStatus InsertChapterMarkersAction::Execute()
{
    PRECONDITION_RETURN(HasValidProject() == true, SERVICE_FAILURE);

    PRECONDITION_RETURN(ConfigureSources() == true, SERVICE_FAILURE);
    PRECONDITION_RETURN(ConfigureTargets() == true, SERVICE_FAILURE);

    PRECONDITION_RETURN(AreChapterMarkersValid(chapterMarkers_) == true, SERVICE_FAILURE);

    ServiceStatus       status = SERVICE_FAILURE;
    NotificationStore supervisor("InsertChapterMarker");

    ReaperProject         currentProject = ReaperProject::Current();
    size_t addedTags = 0;
    for(size_t i = 0; i < chapterMarkers_.size(); i++)
    {
        if(currentProject.InsertChapterMarker(chapterMarkers_[i].Title(), chapterMarkers_[i].Position()) == true)
        {
            addedTags++;
        }
        else
        {
            UnicodeStringStream os;
            os << "Chapter marker '" << chapterMarkers_[i].Title() << "' at position '"
               << SecondsToString(chapterMarkers_[i].Position()) << "' could not be added.";
            supervisor.RegisterError(os.str());
        }
    }

    if(chapterMarkers_.size() != addedTags)
    {
        UnicodeStringStream os;
        os << "Not all chapter markers were added.";
        supervisor.RegisterError(os.str());
    }

    return status;
}

bool InsertChapterMarkersAction::ConfigureTargets()
{
    NotificationStore supervisor("InsertChapterMarker");
    MarkerArray       chapterMarkers;

    FileManager::FILE_TYPE mediaType = FileManager::QueryFileType(source_);
    switch(mediaType)
    {
        case FileManager::FILE_TYPE::MP4CHAPS:
            chapterMarkers = ReadTextFile(source_);
            break;
        case FileManager::FILE_TYPE::MP3:
            chapterMarkers = ReadMP3File(source_);
            break;
        default:
            break;
    }

    if(chapterMarkers.empty() == false)
    {
        chapterMarkers_ = chapterMarkers;
    }

    return chapterMarkers.empty() == false;
}

bool InsertChapterMarkersAction::ConfigureSources()
{
    source_.clear();

    FileDialog fileDialog("Import chapter markers");
    source_ = fileDialog.SelectChaptersFile();
    return source_.empty() == false;
}

MarkerArray InsertChapterMarkersAction::ReadTextFile(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, MarkerArray());

    NotificationStore supervisor("InsertChapterMarker");
    MarkerArray       chapterMarkers;

    const UnicodeStringArray lines = FileManager::ReadTextFile(filename);
    if(lines.empty() == false)
    {
        for(size_t i = 0; i < lines.size(); i++)
        {
            const UnicodeStringArray items = UnicodeStringTokenize(lines[i], ' ');
            if(items.empty() == false)
            {
                const double position = StringToSeconds(items[0]);
                if(position >= 0)
                {
                    UnicodeString name;
                    if(items.size() > 1)
                    {
                        name = items[1];
                    }

                    for(size_t j = 2; j < items.size(); j++)
                    {
                        name += " " + items[j];
                    }

                    //chapterMarkers.push_back(Marker(position, name));
                    chapterMarkers.push_back(ChapterTag(position, name));
                }
                else
                {
                    UnicodeStringStream os;
                    os << "Line " << (i + 1) << ": Invalid timestamp in '" << lines[i] << "'.";
                    supervisor.RegisterError(os.str());
                }
            }
            else
            {
                UnicodeStringStream os;
                os << "Line " << (i + 1) << ": Invalid format in '" << lines[i] << "'.";
                supervisor.RegisterError(os.str());
            }
        }
    }
    else
    {
        UnicodeStringStream os;
        os << "The file '" << filename << "' does not contain chapter markers";
        supervisor.RegisterWarning(os.str());
    }

    return chapterMarkers;
}

MarkerArray InsertChapterMarkersAction::ReadMP3File(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, MarkerArray());

    NotificationStore supervisor("InsertChapterMarker");
    MarkerArray       chapterMarkers;

    return chapterMarkers;
}

}} // namespace ultraschall::reaper
