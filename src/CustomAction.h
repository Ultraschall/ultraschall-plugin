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

#ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_H_INCL__
#define __ULTRASCHALL_REAPER_CUSTOM_ACTION_H_INCL__

#include "ChapterTag.h"
#include "Common.h"
#include "ICustomAction.h"
#include "ReaperProject.h"

namespace ultraschall { namespace reaper {

/// @brief The CustomAction class represents the base class for all custom actions.
class CustomAction : public ICustomAction
{
public:
   /// @brief A constant that specifies an invalid custom action ID.
   static const int32_t INVALID_CUSTOM_ACTION_ID = -1;

   /// @brief Checks whether the specified custom action ID is valid.
   /// @param id The custom action ID to be checked.
   /// @return <b>bool</b> Returns <b>true</b> if the custom action ID is valid; otherwise <b>false</b>.
   static bool IsValidCustomActionId(const int32_t id);

protected:
   /// @brief Checks whether the current REAPER project has already been saved to disk
   /// @return <b>bool</b> Returns <b>true</b> if the current project has been saved; otherwise <b>false</b>.
   static bool HasValidProject();

   /// @brief Checks whether the specified chapter marker positions are within the range of the current recorded audio track.
   /// @param markers The chapter markers to be checked.
   /// @return <b>bool</b> Returns <b>true</b> if the chapter markers are valid; otherwise <b>false</b>.
   static bool AreChapterMarkersValid(const ChapterTagArray& markers);

   /// @brief Returns the current REAPER project.
   /// @return <b>ReaperProject</b> The current REAPER project.
   static ReaperProject CurrentProject();

   /// @brief Returns the directory of the current REAPER project.
   /// @return <b>UnicodeString</b> The directory of the current REAPER project.
   static UnicodeString CurrentProjectDirectory();

   /// @brief Returns the name of the current REAPER project.
   /// @return <b>UnicodeString</b> The name of the current REAPER project.
   static UnicodeString CurrentProjectName();

   /// @brief Creates a project path with the specified extension.
   /// @param extension The optional extension to be used.
   /// @return <b>UnicodeString</b> The project path.
   static UnicodeString CreateProjectPath(const UnicodeString& extension = "");
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_H_INCL__
