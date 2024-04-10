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

#ifndef __ULTRASCHALL_REAPER_ITAG_WRITER_H_INCL__
#define __ULTRASCHALL_REAPER_ITAG_WRITER_H_INCL__

#include "ChapterTag.h"
#include "Common.h"
#include "ServiceStatus.h"
#include "SharedObject.h"

namespace ultraschall { namespace reaper {

/// @brief  The ITagWriter interface provides functions for writing tags to media files.
class ITagWriter : public SharedObject
{
public:
   /// @brief Starts the tag writing process.
   /// @param targetName The name of the target file.
   /// @return <b>true</b> if the tag writing process has been started, <b>false</b> otherwise.
   virtual bool Start(const UnicodeString& targetName)                                                       = 0;

   /// @brief Stops the tag writing process.
   /// @param commit <b>true</b> if the changes should be committed, <b>false</b> otherwise.
   virtual void Stop(const bool commit)                                                                      = 0;

   /// @brief Inserts the specified properties into the target file.
   /// @param targetName The name of the target file.
   /// @param mediaData The properties to be inserted.
   /// @return <b>true</b> if the properties have been inserted, <b>false</b> otherwise.
   virtual bool InsertProperties(const UnicodeString& targetName, const UnicodeStringDictionary& mediaData)  = 0;

   /// @brief Inserts the specified cover image into the target file.
   /// @param targetName The name of the target file.
   /// @param coverImage The cover image to be inserted.
   /// @return <b>true</b> if the cover image has been inserted, <b>false</b> otherwise.
   virtual bool InsertCoverImage(const UnicodeString& targetName, const UnicodeString& coverImage)           = 0;

   /// @brief Inserts the specified chapter markers into the target file.
   /// @param targetName The name of the target file.
   /// @param chapterMarkers The chapter markers to be inserted.
   /// @return <b>true</b> if the chapter markers have been inserted, <b>false</b> otherwise.
   virtual bool InsertChapterMarkers(const UnicodeString& targetName, const ChapterTagArray& chapterMarkers) = 0;

protected:
   virtual ~ITagWriter() {}
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_ITAG_WRITER_H_INCL__
