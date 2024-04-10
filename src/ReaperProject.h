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

#ifndef __ULTRASCHALL_REAPER_PROJECT_H_INCL__
#define __ULTRASCHALL_REAPER_PROJECT_H_INCL__

#include "ChapterTag.h"
#include "Common.h"
#include "ReaperGateway.h"

namespace ultraschall { namespace reaper {

/// @brief The ReaperProject class provides access to the current Reaper project.
class ReaperProject
{
public:
   /// @brief Creates a new ReaperProject instance.
   ReaperProject();

   /// @brief Creates a new ReaperProject instance.
   /// @param nativeReference
   ReaperProject(ProjectReference nativeReference);

   /// @brief Destructor
   virtual ~ReaperProject();

   /// @brief Copy constructor
   /// @param rhs The instance to be copied.
   ReaperProject(const ReaperProject& rhs);

   /// @brief Assignment operator
   /// @param rhs The instance to be assigned.
   /// @return The assigned instance.
   ReaperProject& operator=(const ReaperProject& rhs);

   /// @brief Checks whether the given project is valid.
   /// @param project The project to be checked.
   /// @return <b>true</b> if the project is valid, <b>false</b> otherwise.
   static bool IsValid(const ReaperProject& project);

   /// @brief Checks whether the current project is valid.
   /// @return <b>true</b> if the project is valid, <b>false</b> otherwise.
   bool IsValid() const;

   /// @brief Retrieves the current project.
   /// @return The current project.
   static ReaperProject Current();

   /// @brief Retrieves the current project path.
   /// @return The current project path.
   UnicodeString PathName() const;

   /// @brief Retrieves the current project folder name.
   /// @return The current project folder name.
   UnicodeString FolderName() const;

   /// @brief Retrieves the current project file name.
   /// @return The current project file name.
   UnicodeString FileName() const;

   /// @brief Retrieves the current project name.
   /// @return The current project name.
   UnicodeString Name() const;

   /// @brief Retrieves the current cursor position.
   /// @return The current cursor position.
   double CurrentPosition() const;

   /// @brief Retrieves the minimum position of the current project.
   /// @return The minimum position of the current project.
   double MinPosition() const;

   /// @brief Retrieves the maximum position of the current project.
   /// @return The maximum position of the current project.
   double MaxPosition() const;

   /// @brief Checks whether the given position is with the valid position range.
   /// @param position The position to be checked.
   /// @return <b>true</b> if the position is valid, <b>false</b> otherwise.
   bool IsValidPosition(const double position);

   /// @brief Inserts a new chapter marker at the given position.
   /// @param name The name of the chapter marker.
   /// @param position The position of the chapter marker.
   /// @return <b>true</b> if the chapter marker was inserted successfully, <b>false</b> otherwise.
   bool InsertChapterMarker(const UnicodeString& name, const double position = Globals::INVALID_MARKER_POSITION);

   /// @brief Returns the chapter markers of the current project.
   /// @return The chapter markers of the current project.
   ChapterTagArray ChapterMarkers() const;

   /// @brief Returns the metadata of the current project.
   /// @return The metadata of the current project.
   UnicodeStringDictionary ProjectMetaData() const;

private:
   ProjectReference nativeReference_ = nullptr;

   static UnicodeStringArray SanitizeNotes(const UnicodeString& notes);

   ChapterImageDictionary ChapterImages() const;
   ChapterUrlDictionary ChapterUrls() const;

   static UnicodeString LookupValueInRange(const UnicodeStringDictionary& items, const double position, const double range);

   static UnicodeString CreateProjectMetaDataKey(const UnicodeString& prefix, const UnicodeString& name);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_PROJECT_H_INCL__
