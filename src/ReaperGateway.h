
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

#ifndef __ULTRASCHALL_REAPER_GATEWAY_H_INCL__
#define __ULTRASCHALL_REAPER_GATEWAY_H_INCL__

#include "ChapterTag.h"
#include "Common.h"

namespace ultraschall { namespace reaper {

typedef void* ProjectReference;

/// @brief The ReaperGateway class provides access to the Reaper API.
class ReaperGateway
{
public:
   /// @brief Retrieves the REAPER main window handle.
   /// @return The REAPER main window handle.
   static intptr_t View();

   /// @brief Retrieves the REAPER application version.
   /// @return The REAPER application version.
   static UnicodeString ApplicationVersion();

   /// @brief Registers a custom action with REAPER.
   /// @param name The name of the custom action.
   /// @param infoStruct The custom action information structure.
   /// @return Returns the unique command identifier of the custom action.
   static int32_t RegisterCustomAction(const UnicodeString& name, void* infoStruct);

   /// @brief Retrieves the path to the current REAPER project.
   /// @return The path to the current REAPER project.
   static UnicodeString CurrentProjectPath();

   /// @brief Retrieves the path to the current REAPER project file.
   /// @return The path to the current REAPER project file.
   static UnicodeString CurrentProjectFile();

   /// @brief Retrieves the path to the current REAPER project directory.
   /// @return The path to the current REAPER project directory.
   static UnicodeString CurrentProjectDirectory();

   /// @brief Retrieves the name of the current REAPER project.
   /// @return The name of the current REAPER project.
   static UnicodeString CurrentProjectName();

   /// @brief Converts a timestamp to a string.
   /// @param timestamp The timestamp to convert.
   /// @return The string representation of the timestamp.
   static UnicodeString TimestampToString(const double timestamp);

   /// @brief Converts a string to a timestamp.
   /// @param input The string to convert.
   /// @return The timestamp representation of the string.
   static double StringToTimestamp(const UnicodeString& input);

   /// @brief Retrieves the current project reference.
   /// @return The current project reference.
   static ProjectReference CurrentProject();

   /// @brief Retrieves the project reference for a given REAPER project.
   /// @param projectReference The project path.
   /// @return The project reference.
   static UnicodeString ProjectPath(ProjectReference projectReference);

   /// @brief Retrieves the project notes for a given REAPER project.
   /// @param projectReference The project reference.
   /// @return The project notes.
   static UnicodeString ProjectNotes(ProjectReference projectReference);

   /// @brief  Retrieves the chapter markers for a given REAPER project.
   /// @param projectReference The project reference.
   /// @return The chapter markers.
   static ChapterTagArray Markers(ProjectReference projectReference);

   /// @brief Retrieves the number of chapter markers for a given REAPER project.
   /// @param projectReference The project reference.
   /// @return The number of chapter markers.
   static size_t CountMarkers(ProjectReference projectReference);

   /// @brief Removes the chapter markers from a given REAPER project.
   /// @param projectReference The project reference.
   /// @return <b>true</b> if the chapter markers could be removed, <b>false</b> otherwise.
   static bool ClearMarkers(ProjectReference projectReference);

   /// @brief Inserts a chapter marker into a given REAPER project.
   /// @param projectReference The project reference.
   /// @param name The name of the chapter marker.
   /// @param position The position of the chapter marker.
   /// @return <b>true</b> if the chapter marker could be inserted, <b>false</b> otherwise.
   static bool InsertMarker(ProjectReference projectReference, const UnicodeString& name, const double position);

   /// @brief Inserts a chapter marker into a given REAPER project.
   /// @param projectReference The project reference.
   /// @param marker The chapter marker.
   /// @return <b>true</b> if the chapter marker could be inserted, <b>false</b> otherwise.
   static bool InsertMarker(ProjectReference projectReference, const ChapterTag& marker);

   /// @brief Undos the insertion of a chapter marker at the given position.
   /// @param projectReference The project reference.
   /// @param position The position of the chapter marker.
   /// @return <b>true</b> if the chapter marker could be undone, <b>false</b> otherwise.
   static bool UndoMarker(ProjectReference projectReference, const double position);

   /// @brief Retrieves the playback state of a given REAPER project.
   /// @param projectReference The project reference.
   /// @return The playback state of the project (see REAPER documentation).
   static int PlayState(ProjectReference projectReference);

   /// @brief Retrieves the current cursor position of a given REAPER project.
   /// @param projectReference The project reference.
   /// @return The current cursor position of the project.
   static double CursorPosition(ProjectReference projectReference);

   /// @brief Retrieves the playback position of a given REAPER project.
   /// @param projectReference The project reference.
   /// @return The playback position of the project.
   static double PlayPosition(ProjectReference projectReference);

   /// @brief Retrieves the minimum chapter marker position of a given REAPER project.
   /// @param projectReference The project reference.
   /// @return The minimum chapter marker position of the project.
   static double MinPosition(ProjectReference projectReference);

   /// @brief Retrieves the maximum chapter marker position of a given REAPER project.
   /// @param projectReference The project reference.
   /// @return The maximum chapter marker position of the project.
   static double MaxPosition(ProjectReference projectReference);

   /// @brief Checks whether a system profile value exists.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @return <b>true</b> if the system profile value exists, <b>false</b> otherwise.
   static bool HasSystemValue(const UnicodeString& section, const UnicodeString& key);

   /// @brief Retrieves a system profile value.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @return The value of the system profile value.
   static UnicodeString SystemValue(const UnicodeString& section, const UnicodeString& key);

   /// @brief Sets a system profile value.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @param value The value of the system profile value.
   static void SetSystemValue(const UnicodeString& section, const UnicodeString& key, const UnicodeString& value);

   /// @brief Saves a system profile value.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @param value The value of the system profile value.
   static void SaveSystemValue(const UnicodeString& section, const UnicodeString& key, const UnicodeString& value);

   /// @brief Clears a system profile value.
   /// @param section The name of the section.
   /// @param key The name of the key.
   static void ClearSystemValue(const UnicodeString& section, const UnicodeString& key);

   /// @brief Deletes a system profile value.
   /// @param section The name of the section.
   /// @param key The name of the key.
   static void DeleteSystemValue(const UnicodeString& section, const UnicodeString& key);

   /// @brief Checks whether a profile value exists.
   /// @param profile The name of the profile.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @return <b>true</b> if the profile value exists, <b>false</b> otherwise.
   static bool HasProfileValue(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key);

   /// @brief Retrieves a profile value.
   /// @param profile The name of the profile.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @return The value of the profile value.
   static UnicodeString ProfileValue(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key);

   /// @brief Sets a profile value.
   /// @param profile The name of the profile.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @param value The value of the profile value.
   /// @return <b>true</b> if the profile value could be set, <b>false</b> otherwise.
   static bool SetProfileValue(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const UnicodeString& value);

   /// @brief Saves a profile value.
   /// @param profile The name of the profile.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @param value The value of the profile value.
   /// @return <b>true</b> if the profile value could be saved, <b>false</b> otherwise.
   static bool SaveProfileValue(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const UnicodeString& value);

   /// @brief Clears a profile value.
   /// @param profile The name of the profile.
   /// @param section The name of the section.
   /// @param key The name of the key.
   static void ClearProfileValue(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key);

   /// @brief Deletes a profile value.
   /// @param profile The name of the profile.
   /// @param section The name of the section.
   /// @param key The name of the key.
   static void DeleteProfileValue(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key);

   /// @brief Checks whether a project value exists.
   /// @param projectReference The project reference.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @return <b>true</b> if the project value exists, <b>false</b> otherwise.
   static bool HasProjectValue(ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key);

   /// @brief Retrieves a project value.
   /// @param projectReference The project reference.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @return The value of the project value.
   static UnicodeString QueryProjectValue(ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key);

   /// @brief Sets a project value.
   /// @param projectReference The project reference.
   /// @param section The name of the section.
   /// @param key The name of the key.
   /// @param value The value of the project value.
   static void SetProjectValue(ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key, const UnicodeString& value);

   /// @brief Saves a project value.
   /// @param projectReference The project reference.
   /// @param section The name of the section.
   /// @param key The name of the key.
   static void ClearProjectValue(ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key);

   /// @brief Clears all project values.
   /// @param projectReference The project reference.
   /// @param section The name of the section.
   static void ClearProjectValues(ProjectReference projectReference, const UnicodeString& section);

   /// @brief Queries all project values with a profile section.
   /// @param projectReference The project reference.
   /// @param section The name of the section.
   /// @return The project values.
   static UnicodeStringDictionary QueryProjectValues(ProjectReference projectReference, const UnicodeString& section);

   /// @brief Retrieves the project metadata for a given REAPER project.
   /// @param projectReference The project reference.
   /// @param key The name of the key.
   /// @return The project metadata.
   static UnicodeString ProjectMetaData(ProjectReference projectReference, const UnicodeString& key);

private:
   static const size_t MAX_REAPER_STRING_BUFFER_SIZE = 4096;

   static UnicodeString fullProfilePath_;
   static UnicodeString FullProfilePath(const UnicodeString& profile);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_GATEWAY_H_INCL__
