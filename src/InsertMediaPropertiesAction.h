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

#ifndef __ULTRASCHALL_REAPER_INSERT_MEDIA_PROPERTIES_ACTION_H_INCL__
#define __ULTRASCHALL_REAPER_INSERT_MEDIA_PROPERTIES_ACTION_H_INCL__

#include "Common.h"
#include "CustomAction.h"

namespace ultraschall { namespace reaper {

class ITagWriter;

/// @brief The InsertMediaPropertiesAction class implements the action that inserts media properties into a MP3 file.
class InsertMediaPropertiesAction : public CustomAction
{
public:
   /// @brief Returns the unique identifier of the action.
   /// @return The unique identifier of the action.
   static const UnicodeChar* UniqueId()
   {
      return "ULTRASCHALL_INSERT_MEDIA_PROPERTIES";
   }

   /// @brief Returns the unique name of the action.
   /// @return The unique name of the action.
   static const UnicodeChar* UniqueName()
   {
      return "ULTRASCHALL: Insert media properties into target...";
   }

   /// @brief Creates a new instance of the action.
   /// @return A new instance of the action.
   static ICustomAction* CreateCustomAction()
   {
      return new InsertMediaPropertiesAction();
   }

   /// @brief Executes the action.
   /// @return The status of the action.
   virtual ServiceStatus Execute() override;

private:
   bool ConfigureTargets();
   bool ConfigureSources();

   UnicodeString FindCoverImage();
   UnicodeStringArray FindMissingMediaData();

   UnicodeStringArray targets_;
   UnicodeString coverImage_;
   ChapterTagArray chapterMarkers_;
   UnicodeStringDictionary mediaData_;
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_INSERT_MEDIA_PROPERTIES_ACTION_H_INCL__
