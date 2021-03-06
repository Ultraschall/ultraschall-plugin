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

#include "ReaperGateway.h"
#include "PlatformGateway.h"
#include "FileManager.h"
#include "ReaperEntryPoints.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

UnicodeString ReaperGateway::fullProfilePath_ = "";

intptr_t ReaperGateway::View()
{
    return reinterpret_cast<intptr_t>(reaper_api::GetMainHwnd());
}

UnicodeString ReaperGateway::ApplicationVersion()
{
    return H2U(reaper_api::GetAppVersion());
}

int32_t ReaperGateway::RegisterCustomAction(const UnicodeString& name, void* infoStruct)
{
    PRECONDITION_RETURN(name.empty() == false, -1);

    return reaper_api::plugin_register(U2H(name).c_str(), infoStruct);
}

ProjectReference ReaperGateway::CurrentProject()
{
    return reinterpret_cast<ProjectReference>(reaper_api::EnumProjects(-1, 0, 0));
}

UnicodeString ReaperGateway::CurrentProjectPath()
{
    UnicodeString result;

    char             buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
    ProjectReference projectReference = reaper_api::EnumProjects(-1, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
    if((projectReference != nullptr) && (strlen(buffer) > 0))
    {
        result = buffer;
    }

    return result;
}

UnicodeString ReaperGateway::CurrentProjectFile()
{
    UnicodeString result;

    const UnicodeString projectPath = CurrentProjectPath();
    if(projectPath.empty() == false)
    {
        const UnicodeStringArray pathComponents = FileManager::SplitPath(projectPath);
        if(pathComponents.empty() == false)
        {
            result = pathComponents[pathComponents.size() - 1];
        }
    }

    return result;
}

UnicodeString ReaperGateway::CurrentProjectDirectory()
{
    UnicodeString result;

    const UnicodeString projectPath = CurrentProjectPath();
    if(projectPath.empty() == false)
    {
        const UnicodeStringArray pathComponents = FileManager::SplitPath(projectPath);
        if(pathComponents.empty() == false)
        {
            for(size_t i = 0; i < pathComponents.size() - 1; i++)
            {
                result += pathComponents[i];
                if(i < pathComponents.size() - 2)
                {
                    result += FileManager::PathSeparator();
                }
            }
        }
    }

    return result;
}

UnicodeString ReaperGateway::CurrentProjectName()
{
    UnicodeString result;

    const UnicodeString projectFile = CurrentProjectFile();
    if(projectFile.empty() == false)
    {
        result = projectFile.substr(0, projectFile.find('.', 0));
    }

    return result;
}

struct Timestamp
{
    int hours;
    int minutes;
    int seconds;
    int milliSeconds;

    Timestamp() : hours(0), minutes(0), seconds(0), milliSeconds(0) {}

    static Timestamp FromString(const UnicodeString& str)
    {
        UnicodeStringArray items = UnicodeStringTokenize(str, ':');
        std::reverse(items.begin(), items.end());

        Timestamp timestamp;

        UnicodeStringArray buffer = UnicodeStringTokenize(items[0], '.');
        for(size_t i = 0; i < buffer.size(); ++i)
        {
            switch(i)
            {
                case 0:
                    timestamp.seconds = std::atoi(buffer[0].c_str());
                    break;

                case 1:
                    timestamp.milliSeconds = std::atoi(buffer[1].c_str());
                    break;

                default:
                    break;
            }
        }

        for(size_t i = 0; i < items.size(); ++i)
        {
            switch(i)
            {
                case 1:
                    timestamp.minutes = std::atoi(items[1].c_str());
                    break;

                case 2:
                    timestamp.hours = std::atoi(items[2].c_str());
                    break;

                default:
                    break;
            }
        }

        return timestamp;
    }

    UnicodeString ToString() const
    {
        std::stringstream buffer;
        buffer << std::setfill('0');
        buffer << std::setw(2) << hours << ":";
        buffer << std::setw(2) << minutes << ":";
        buffer << std::setw(2) << seconds << ".";
        buffer << std::setw(3) << milliSeconds;

        return buffer.str();
    }
};

UnicodeString ReaperGateway::TimestampToString(const double timestamp)
{
    UnicodeString result;

    char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
    reaper_api::format_timestr_pos(timestamp, buffer, MAX_REAPER_STRING_BUFFER_SIZE, 0);
    if(strlen(buffer) > 0)
    {
        result = Timestamp::FromString(buffer).ToString();
    }

    return result;
}

double ReaperGateway::StringToTimestamp(const UnicodeString& input)
{
    PRECONDITION_RETURN(input.empty() == false, -1);
    return reaper_api::parse_timestr(input.c_str());
}

UnicodeString ReaperGateway::ProjectPath(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, UnicodeString());

    UnicodeString projectPath;

    ReaProject*         nativeReference                       = reinterpret_cast<ReaProject*>(projectReference);
    static const size_t MAX_REAPER_STRING_BUFFER_SIZE         = 4096;
    char                buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
    int                 index                                 = 0;
    ProjectReference    externalReference =
        (ProjectReference)reaper_api::EnumProjects(index++, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
    while((externalReference != 0) && (projectPath.empty() == true))
    {
        if(externalReference == nativeReference)
        {
            projectPath = buffer;
        }

        externalReference = (ProjectReference)reaper_api::EnumProjects(index++, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
    }

    return projectPath;
}

UnicodeString ReaperGateway::ProjectNotes(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, UnicodeString());

    UnicodeString projectNotes;

    ReaProject*         nativeReference                = reinterpret_cast<ReaProject*>(projectReference);
    static const size_t MAX_PROJECT_NOTES_SIZE         = 4096;
    char                buffer[MAX_PROJECT_NOTES_SIZE] = {0};
    reaper_api::GetSetProjectNotes(nativeReference, false, buffer, (int)MAX_PROJECT_NOTES_SIZE);
    projectNotes = H2U(buffer);
    projectNotes.erase(std::remove(projectNotes.begin(), projectNotes.end(), '\r'), projectNotes.end());

    return projectNotes;
}

bool IsEditMarker(const UnicodeString& name)
{
    PRECONDITION_RETURN(name.empty() == false, false);

    const UnicodeString normalizedName = UnicodeStringCopyTrimLeft(name);
    PRECONDITION_RETURN(normalizedName.empty() == false, false);

    return (normalizedName.size() >= 5) && (normalizedName.substr(0, 5) == "_Edit");
}

ChapterTagArray ReaperGateway::Markers(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, ChapterTagArray());

    ChapterTagArray allMarkers;

    bool        isRegion        = false;
    double      position        = 0;
    double      duration        = 0;
    const char* name            = 0;
    int         number          = 0;
    int         color           = 0;
    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    int         nextIndex =
        reaper_api::EnumProjectMarkers3(nativeReference, 0, &isRegion, &position, &duration, &name, &number, &color);
    while(nextIndex > 0)
    {
        if(IsEditMarker(name) == false) // remove edit markers
        {
            if(false == isRegion) // remove regions
            {
                allMarkers.push_back(ChapterTag(position, name));
            }
        }

        nextIndex = reaper_api::EnumProjectMarkers3(
            nativeReference, nextIndex, &isRegion, &position, &duration, &name, &number, &color);
    }

    return allMarkers;
}

size_t ReaperGateway::CountMarkers(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    int         numMarkers      = -1;
    reaper_api::CountProjectMarkers(nativeReference, &numMarkers, 0);
    return static_cast<size_t>(numMarkers);
}

bool ReaperGateway::ClearMarkers(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);

    ReaProject*  nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    const size_t numMarkers      = CountMarkers(projectReference);
    for(size_t i = 0; i < numMarkers; i++)
    {
        reaper_api::DeleteProjectMarkerByIndex(nativeReference, int(i));
    }

    return true;
}

bool ReaperGateway::InsertMarker(ProjectReference projectReference, const UnicodeString& name, const double position)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);
    PRECONDITION_RETURN(position >= 0, false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    return reaper_api::AddProjectMarker2(nativeReference, false, position, 0, name.c_str(), -1, 0) != -1;
}

bool ReaperGateway::InsertMarker(ProjectReference projectReference, const ChapterTag& marker)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    return reaper_api::AddProjectMarker2(
               nativeReference, false, marker.Position(), 0, marker.Title().c_str(), -1,
               Globals::DEFAULT_CHAPTER_MARKER_COLOR) != -1;
}

bool ReaperGateway::UndoMarker(ProjectReference projectReference, const double position)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);
    PRECONDITION_RETURN(position >= 0, false);

    bool        undone          = false;
    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    int         markerIndex     = -1;
    reaper_api::GetLastMarkerAndCurRegion(nativeReference, position, &markerIndex, 0);
    if(markerIndex != -1)
    {
        undone = reaper_api::DeleteProjectMarkerByIndex(nativeReference, markerIndex);
    }

    return undone;
}

int ReaperGateway::PlayState(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    return reaper_api::GetPlayStateEx(nativeReference);
}

double ReaperGateway::CursorPosition(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    return reaper_api::GetCursorPositionEx(nativeReference);
}

double ReaperGateway::PlayPosition(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    return reaper_api::GetPlayPositionEx(nativeReference);
}

double ReaperGateway::MinPosition(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    double minPosition = MaxPosition(projectReference);
    if(minPosition != Globals::INVALID_MARKER_POSITION)
    {
        ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
        int         i               = 0;
        MediaItem*  mediaItem       = reaper_api::GetMediaItem(nativeReference, i++);
        while(mediaItem != 0)
        {
            double startPosition = reaper_api::GetMediaItemInfo_Value(mediaItem, "D_POSITION");
            if(startPosition < minPosition)
            {
                minPosition = startPosition;
            }
            mediaItem = reaper_api::GetMediaItem(nativeReference, i++);
        }
    }

    return minPosition;
}

double ReaperGateway::MaxPosition(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    double      maxPosition     = Globals::INVALID_MARKER_POSITION;
    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    int         i               = 0;
    MediaItem*  mediaItem       = reaper_api::GetMediaItem(nativeReference, i++);
    while(mediaItem != 0)
    {
        const double endPosition = reaper_api::GetMediaItemInfo_Value(mediaItem, "D_POSITION") +
                                   reaper_api::GetMediaItemInfo_Value(mediaItem, "D_LENGTH");
        if((endPosition >= 0) && (endPosition > maxPosition))
        {
            maxPosition = endPosition;
        }

        mediaItem = reaper_api::GetMediaItem(nativeReference, i++);
    }

    return maxPosition;
}

bool ReaperGateway::HasSystemValue(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(section.empty() == false, false);
    PRECONDITION_RETURN(key.empty() == false, false);

    return reaper_api::HasExtState(U2H(section).c_str(), U2H(key).c_str());
}

UnicodeString ReaperGateway::SystemValue(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(section.empty() == false, UnicodeString());
    PRECONDITION_RETURN(key.empty() == false, UnicodeString());

    return H2U(reaper_api::GetExtState(U2H(section).c_str(), U2H(key).c_str()));
}

void ReaperGateway::SetSystemValue(const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);
    PRECONDITION(value.empty() == false);

    reaper_api::SetExtState(U2H(section).c_str(), U2H(key).c_str(), U2H(value).c_str(), false);
}

void ReaperGateway::SaveSystemValue(const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);
    PRECONDITION(value.empty() == false);

    reaper_api::SetExtState(U2H(section).c_str(), U2H(key).c_str(), U2H(value).c_str(), true);
}

void ReaperGateway::ClearSystemValue(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    reaper_api::DeleteExtState(U2H(section).c_str(), U2H(key).c_str(), false);
}

void ReaperGateway::DeleteSystemValue(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    reaper_api::DeleteExtState(U2H(section).c_str(), U2H(key).c_str(), true);
}

bool ReaperGateway::HasProfileValue(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
{
    return ProfileValue(profile, section, key).empty() == false;
}

UnicodeString ReaperGateway::ProfileValue(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
{
    UnicodeString value;

    PRECONDITION_RETURN(profile.empty() == false, UnicodeString());
    PRECONDITION_RETURN(section.empty() == false, UnicodeString());
    PRECONDITION_RETURN(key.empty() == false, UnicodeString());

    const UnicodeString fullProfilePath                       = FullProfilePath(profile);
    UnicodeChar         buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
    uint32_t            bufferSize                            = MAX_REAPER_STRING_BUFFER_SIZE;
    uint32_t            result                                = GetPrivateProfileString(
        U2H(section).c_str(), U2H(key).c_str(), 0, buffer, bufferSize, U2H(fullProfilePath).c_str());
    if(result > 0)
    {
        value = H2U(buffer);
    }

    return value;
}

bool ReaperGateway::SetProfileValue(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    return SaveProfileValue(profile, section, key, value);
}

bool ReaperGateway::SaveProfileValue(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION_RETURN(profile.empty() == false, false);
    PRECONDITION_RETURN(section.empty() == false, false);
    PRECONDITION_RETURN(key.empty() == false, false);
    PRECONDITION_RETURN(value.empty() == false, false);

    const UnicodeString fullProfilePath = FullProfilePath(profile);
    return WritePrivateProfileString(
        U2H(section).c_str(), U2H(key).c_str(), U2H(value).c_str(), U2H(fullProfilePath).c_str());
}

void ReaperGateway::ClearProfileValue(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
{
    DeleteProfileValue(profile, section, key);
}

void ReaperGateway::DeleteProfileValue(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
{
    SaveProfileValue(profile, section, key, "");
}

bool ReaperGateway::HasProjectValue(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);
    PRECONDITION_RETURN(section.empty() == false, false);
    PRECONDITION_RETURN(key.empty() == false, false);

    ReaProject*         nativeReference                = reinterpret_cast<ReaProject*>(projectReference);
    static const size_t MAX_PROJECT_VALUE_SIZE         = 4096;
    char                buffer[MAX_PROJECT_VALUE_SIZE] = {0};
    const int           valueSize                      = reaper_api::GetProjExtState(
        nativeReference, U2H(section).c_str(), U2H(key).c_str(), buffer, (int)MAX_PROJECT_VALUE_SIZE);
    return valueSize > 0;
}

UnicodeString ReaperGateway::QueryProjectValue(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(projectReference != nullptr, UnicodeString());
    PRECONDITION_RETURN(section.empty() == false, UnicodeString());
    PRECONDITION_RETURN(key.empty() == false, UnicodeString());

    UnicodeString projectValue;

    ReaProject*         nativeReference                = reinterpret_cast<ReaProject*>(projectReference);
    static const size_t MAX_PROJECT_VALUE_SIZE         = 4096;
    char                buffer[MAX_PROJECT_VALUE_SIZE] = {0};
    const int           valueSize                      = reaper_api::GetProjExtState(
        nativeReference, U2H(section).c_str(), U2H(key).c_str(), buffer, (int)MAX_PROJECT_VALUE_SIZE);
    if(valueSize > 0)
    {
        projectValue = H2U(buffer);
    }

    return projectValue;
}

void ReaperGateway::SetProjectValue(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key,
    const UnicodeString& value)
{
    PRECONDITION(projectReference != nullptr);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);
    PRECONDITION(value.empty() == false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    reaper_api::SetProjExtState(nativeReference, U2H(section).c_str(), U2H(key).c_str(), U2H(value).c_str());
}

void ReaperGateway::ClearProjectValue(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION(projectReference != nullptr);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    reaper_api::SetProjExtState(nativeReference, U2H(section).c_str(), U2H(key).c_str(), nullptr);
}

void ReaperGateway::ClearProjectValues(ProjectReference projectReference, const UnicodeString& section)
{
    PRECONDITION(projectReference != nullptr);
    PRECONDITION(section.empty() == false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    reaper_api::SetProjExtState(nativeReference, U2H(section).c_str(), nullptr, nullptr);
}

UnicodeStringDictionary ReaperGateway::QueryProjectValues(
    ProjectReference projectReference, const UnicodeString& section)
{
    PRECONDITION_RETURN(projectReference != nullptr, UnicodeStringDictionary());
    PRECONDITION_RETURN(section.empty() == false, UnicodeStringDictionary());

    ReaProject*         nativeReference        = reinterpret_cast<ReaProject*>(projectReference);
    static const size_t MAX_BUFFER_SIZE        = 4096;
    char                key[MAX_BUFFER_SIZE]   = {0};
    char                value[MAX_BUFFER_SIZE] = {0};

    UnicodeStringDictionary values;

    int  i        = 0;
    bool hasValue = reaper_api::EnumProjExtState(
        nativeReference, U2H(section).c_str(), i++, key, MAX_BUFFER_SIZE, value, MAX_BUFFER_SIZE);
    while(true == hasValue)
    {
        values.insert(std::pair<UnicodeString, UnicodeString>(key, value));

        memset(key, 0, MAX_BUFFER_SIZE * sizeof(char));
        memset(value, 0, MAX_BUFFER_SIZE * sizeof(char));
        hasValue = reaper_api::EnumProjExtState(
            nativeReference, U2H(section).c_str(), i++, key, MAX_BUFFER_SIZE, value, MAX_BUFFER_SIZE);
    }

    return values;
}

UnicodeString ReaperGateway::ProjectMetaData(ProjectReference projectReference, const UnicodeString& key)
{
    PRECONDITION_RETURN(projectReference != nullptr, UnicodeString());
    PRECONDITION_RETURN(key.empty() == false, UnicodeString());

    UnicodeString data;

    ReaProject*         nativeReference        = reinterpret_cast<ReaProject*>(projectReference);
    static const size_t MAX_BUFFER_SIZE        = 4096;
    char                value[MAX_BUFFER_SIZE] = {0};

    strncpy(value, key.c_str(), (key.length() < MAX_BUFFER_SIZE) ? key.length() : MAX_BUFFER_SIZE);
    if(reaper_api::GetSetProjectInfo_String(nativeReference, "RENDER_METADATA", value, false))
    {
        data = H2U(value);
    }

    return data;
}

UnicodeString ReaperGateway::FullProfilePath(const UnicodeString& profile)
{
    if(fullProfilePath_.empty() == true)
    {
        fullProfilePath_ = PlatformGateway::QueryReaperProfilePath();
    }

    return FileManager::AppendPath(fullProfilePath_, profile);
}

}} // namespace ultraschall::reaper
