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

#include "ReaperProject.h"
#include "Application.h"
#include "FileManager.h"
#include "NotificationStore.h"
#include "HttpClient.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

ReaperProject::ReaperProject() {}

ReaperProject::ReaperProject(ProjectReference nativeReference) : nativeReference_(nativeReference) {}

ReaperProject::~ReaperProject()
{
    nativeReference_ = nullptr;
}

ReaperProject::ReaperProject(const ReaperProject& rhs)
{
    *this = rhs;
}

ReaperProject& ReaperProject::operator=(const ReaperProject& rhs)
{
    if(this != &rhs)
    {
        nativeReference_ = rhs.nativeReference_;
    }

    return *this;
}

bool ReaperProject::IsValid() const
{
    return nativeReference_ != nullptr;
}

bool ReaperProject::IsValid(const ReaperProject& project)
{
    return project.IsValid();
}

ReaperProject ReaperProject::Current()
{
    return ReaperProject(ReaperGateway::CurrentProject());
}

UnicodeString ReaperProject::PathName() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, UnicodeString());
    return ReaperGateway::ProjectPath(nativeReference_);
}

UnicodeString ReaperProject::FolderName() const
{
    UnicodeString result;

    const UnicodeString fullPath = PathName();
    if(fullPath.empty() == false)
    {
        const char               pathSeparator  = FileManager::PathSeparator();
        const UnicodeStringArray pathComponents = UnicodeStringTokenize(fullPath, pathSeparator);
        if(pathComponents.empty() == false)
        {
            for(size_t i = 0; i < pathComponents.size() - 1; i++)
            {
                result += pathComponents[i];
                if(i < pathComponents.size() - 2)
                {
                    result += pathSeparator;
                }
            }
        }
    }

    return result;
}

UnicodeString ReaperProject::FileName() const
{
    UnicodeString result;

    const UnicodeString fullPath = PathName();
    if(fullPath.empty() == false)
    {
        const char               pathSeparator  = FileManager::PathSeparator();
        const UnicodeStringArray pathComponents = UnicodeStringTokenize(fullPath, pathSeparator);
        if(pathComponents.empty() == false)
        {
            result = pathComponents[pathComponents.size() - 1];
        }
    }

    return result;
}

UnicodeString ReaperProject::Name() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, UnicodeString());

    UnicodeString result;

    const UnicodeString file = FileName();
    if(file.empty() == false)
    {
        result = file.substr(0, file.rfind('.'));
    }

    return result;
}

UnicodeStringArray ReaperProject::SanitizeNotes(const UnicodeString& source)
{
    PRECONDITION_RETURN(source.empty() == false, UnicodeStringArray());

    UnicodeStringArray result;

    static const UnicodeChar TOKEN_DELIMITER      = '\n';
    static const size_t      REQUIRED_TOKEN_COUNT = 6;

    UnicodeStringArray sanitizedSource = UnicodeStringTokenize(source, TOKEN_DELIMITER);
    if(sanitizedSource.size() <= REQUIRED_TOKEN_COUNT)
    {
        while(sanitizedSource.size() < REQUIRED_TOKEN_COUNT)
        {
            sanitizedSource.push_back("");
        }

        std::for_each(sanitizedSource.begin(), sanitizedSource.end(), [&](const UnicodeString str) {
            if(str == "\n")
            {
                result.push_back("");
            }
            else
            {
                result.push_back(str);
            }
        });
    }

    return result;
}

UnicodeStringDictionary ReaperProject::ParseNotes() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, UnicodeStringDictionary());

    static const UnicodeStringArray keys
        = {"podcast", "author", "episode", "publicationDate", "category", "description"};

    UnicodeStringDictionary notesDictionary;
    UnicodeString           notes = ReaperGateway::ProjectNotes(nativeReference_);
    if(notes.empty() == false)
    {
        const UnicodeStringArray values = SanitizeNotes(notes);
        if(values.size() == keys.size())
        {
            for(size_t i = 0; i < values.size(); i++)
            {
                notesDictionary.insert(std::pair<UnicodeString, UnicodeString>(keys[i], values[i]));
            }
        }
        else
        {
            NotificationStore notificationStore("ULTRASCHALL_PROJECT_VALIDITY_CHECK");
            notificationStore.RegisterWarning("The MP3 metadata is invalid. Please check and retry.");
        }
    }

    return notesDictionary;
}

bool ReaperProject::InsertChapterMarker(const UnicodeString& name, const double position)
{
    PRECONDITION_RETURN(nativeReference_ != 0, false);
    PRECONDITION_RETURN(name.empty() == false, false);

    double actualPosition = (position != Globals::INVALID_MARKER_POSITION) ? position : CurrentPosition();

    return ReaperGateway::InsertMarker(nativeReference_, name, actualPosition);
}

double ReaperProject::CurrentPosition() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, Globals::INVALID_MARKER_POSITION);

    double    currentPosition = Globals::INVALID_MARKER_POSITION;
    const int playState       = ReaperGateway::PlayState(nativeReference_);
    if((playState == 0) || (playState == 2))
    {
        currentPosition = ReaperGateway::CursorPosition(nativeReference_);
    }
    else
    {
        currentPosition = ReaperGateway::PlayPosition(nativeReference_);
    }

    return currentPosition;
}

double ReaperProject::MinPosition() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, Globals::INVALID_MARKER_POSITION);

    return ReaperGateway::MinPosition(nativeReference_);
}

double ReaperProject::MaxPosition() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, Globals::INVALID_MARKER_POSITION);

    return ReaperGateway::MaxPosition(nativeReference_);
}

bool ReaperProject::IsValidPosition(const double position)
{
    PRECONDITION_RETURN(nativeReference_ != 0, false);

    return (position >= 0) && (position <= MaxPosition());
}

ChapterTagArray ReaperProject::ChapterMarkers() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, ChapterTagArray());

    ChapterTagArray markers = ReaperGateway::Markers(nativeReference_);
    if(markers.empty() == false)
    {
        ChapterImageArray images = ChapterImages();
        ChapterUrlArray   urls   = ChapterUrls();
        MapImagesAndUrlsToChapters(images, urls, markers);
    }

    return markers;
}

ChapterImageArray ReaperProject::ChapterImages() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, ChapterImageArray());

    ChapterImageArray images;

    UnicodeStringDictionary locatedImages = ReaperGateway::QueryProjectValues(nativeReference_, "chapterimages");
    if(locatedImages.empty() == false)
    {
        std::for_each(
            locatedImages.begin(), locatedImages.end(), [&](const std::pair<UnicodeString, UnicodeString>& item) {
                const double        position = std::stod(item.first);
                const UnicodeString uri      = item.second;
                images.push_back(ChapterImage(position, uri));
            });
    }

    UnicodeStringDictionary unlocatedImages = ReaperGateway::QueryProjectValues(nativeReference_, "lostimages");
    if(unlocatedImages.empty() == false)
    {
        std::for_each(
            unlocatedImages.begin(), unlocatedImages.end(), [&](const std::pair<UnicodeString, UnicodeString>& item) {
                const double        position = std::stod(item.first);
                const UnicodeString uri      = item.second;
                images.push_back(ChapterImage(position, uri));
            });
    }

    return images;
}

ChapterUrlArray ReaperProject::ChapterUrls() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, ChapterUrlArray());

    ChapterUrlArray urls;

    UnicodeStringDictionary urlDictionary = ReaperGateway::QueryProjectValues(nativeReference_, "chapterurls");
    if(urlDictionary.empty() == false)
    {
        std::for_each(
            urlDictionary.begin(), urlDictionary.end(), [&](const std::pair<UnicodeString, UnicodeString>& item) {
                const double        position = std::stod(item.first);
                const UnicodeString uri      = UnicodeStringCopyTrim(item.second);
                urls.push_back(ChapterUrl(position, uri));
            });
    }

    return urls;
}

void ReaperProject::MapImagesAndUrlsToChapters(
    const ChapterImageArray& images, const ChapterUrlArray& urls, ChapterTagArray& chapters)
{
    PRECONDITION(chapters.empty() == false);

    static const double POSITION_DEAD_BAND = 2.0;

    std::for_each(images.begin(), images.end(), [&](const ChapterImage& image) {
        std::for_each(chapters.begin(), chapters.end(), [&](ChapterTag& chapter) {
            if(std::fabs(image.Position() - chapter.Position()) < POSITION_DEAD_BAND)
            {
                chapter.SetImage(image.Uri());
            }
        });
    });

    std::for_each(urls.begin(), urls.end(), [&](const ChapterUrl& url) {
        std::for_each(chapters.begin(), chapters.end(), [&](ChapterTag& chapter) {
            if(std::fabs(url.Position() - chapter.Position()) < POSITION_DEAD_BAND)
            {
                //chapter.SetUrl(HttpClient::EncodeUrl(url.Uri()));
                chapter.SetUrl(url.Uri());
            }
        });
    });
}

}} // namespace ultraschall::reaper
