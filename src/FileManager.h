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

#ifndef __ULTRASCHALL_REAPER_FILE_MANAGER_H_INCL__
#define __ULTRASCHALL_REAPER_FILE_MANAGER_H_INCL__

#include "BinaryStream.h"
#include "Common.h"

namespace ultraschall { namespace reaper {

class FileManager
{
public:
   static UnicodeChar PathSeparator();

   static UnicodeString AppendPath(const UnicodeString& prefix, const UnicodeString& appendix);
   static UnicodeString StripPath(const UnicodeString& path);
   static UnicodeStringArray SplitPath(const UnicodeString& path);

   static bool FileExists(const UnicodeString& path);
   static size_t FileExists(const UnicodeStringArray& paths);

   static std::string FindFile(const UnicodeString& path, const UnicodeString& name);
   static std::string FindFile(const UnicodeString& path, const UnicodeStringArray& names);

   static UnicodeString QueryFileDirectory(const UnicodeString& filename);

   enum class FILE_TYPE
   {
      MP4CHAPS,
      MP3,
      JPEG,
      PNG,
      UNKNOWN_FILE_TYPE,
      MAX_FILE_TYPE = UNKNOWN_FILE_TYPE
   };
   static FILE_TYPE QueryFileType(const UnicodeString& filename);

   static size_t QueryFileSize(const UnicodeString& filename);
   static bool IsDiskSpaceAvailable(const UnicodeString& filename, const size_t requiredBytes);

   static BinaryStream* ReadBinaryFile(const UnicodeString& filename);
   static UnicodeStringArray ReadTextFile(const UnicodeString& filename);

   static bool WriteTextFile(const UnicodeString& filename, const UnicodeString& str);

private:
   static UnicodeString NormalizeFileName(const UnicodeString& targetName);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_FILE_MANAGER_H_INCL__
