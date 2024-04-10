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

/// @brief The FileManager class provides a set of file management functions.
class FileManager
{
public:
   /// @brief Returns the path separator for the current operating system.
   /// @return <b>UnicodeChar</b> The path separator.
   static UnicodeChar PathSeparator();

   /// @brief Appends the specified appendix to the specified prefix.
   /// @param prefix The prefix to which the appendix will be appended.
   /// @param appendix The appendix to be appended to the prefix.
   /// @return <b>UnicodeString</b> The resulting path.
   static UnicodeString AppendPath(const UnicodeString& prefix, const UnicodeString& appendix);

   /// @brief Strips the path from the specified path.
   /// @param path The path from which the path will be stripped.
   /// @return <b>UnicodeString</b> The stripped path.
   static UnicodeString StripPath(const UnicodeString& path);

   /// @brief Splits the specified path into its components.
   /// @param path The path to be split.
   /// @return <b>UnicodeStringArray</b> The components of the path.
   static UnicodeStringArray SplitPath(const UnicodeString& path);

   /// @brief Checks whether the specified file exists.
   /// @param path The path to the file to be checked.
   /// @return <b>bool</b> Returns <b>true</b> if the file exists; otherwise <b>false</b>.
   static bool FileExists(const UnicodeString& path);

   /// @brief Checks whether the specified files exist.
   /// @param paths The paths to the files to be checked.
   /// @return <b>size_t</b> The number of files that exist.
   static size_t FileExists(const UnicodeStringArray& paths);

   /// @brief Searches for the specified file in the specified path.
   /// @param path The path in which the file will be searched.
   /// @param name The name of the file to be searched.
   /// @return <b>std::string</b> The full path of the file if it exists; otherwise an empty string.
   static std::string FindFile(const UnicodeString& path, const UnicodeString& name);

   /// @brief Searches for the specified files in the specified path.
   /// @param path The path in which the files will be searched.
   /// @param names The names of the files to be searched.
   /// @return <b>std::string</b> The full path of the file if it exists; otherwise an empty string.
   static std::string FindFile(const UnicodeString& path, const UnicodeStringArray& names);

   /// @brief Returns the directory of the specified file.
   /// @param filename The name of the file for which the directory will be returned.
   /// @return <b>UnicodeString</b> The directory of the file.
   static UnicodeString QueryFileDirectory(const UnicodeString& filename);

   /// @brief Returns the file type of the specified file.
   enum class FILE_TYPE
   {
      /// @brief The file is a text file with MP4CHAPS.
      MP4CHAPS,
      /// @brief The file is an MP3 file.
      MP3,
      /// @brief The file is a JPEG file.
      JPEG,
      /// @brief The file is a PNG file.
      PNG,
      /// @brief The file type is unknown.
      UNKNOWN_FILE_TYPE,
      MAX_FILE_TYPE = UNKNOWN_FILE_TYPE
   };

   /// @brief Queries the file type of the specified file.
   /// @param filename The name of the file for which the file type will be queried.
   /// @return <b>FILE_TYPE</b> The file type of the file.
   static FILE_TYPE QueryFileType(const UnicodeString& filename);

   /// @brief Queries the size of the specified file.
   /// @param filename The name of the file for which the size will be queried.
   /// @return <b>size_t</b> The size of the file.
   static size_t QueryFileSize(const UnicodeString& filename);

   /// @brief Checks whether the specified data size is available on the disk (checked against the users disk quota).
   /// @param filename  The name of the file for which the disk space will be checked.
   /// @param requiredBytes The number of bytes that are required.
   /// @return <b>bool</b> Returns <b>true</b> if the required disk space is available; otherwise <b>false</b>.
   static bool IsDiskSpaceAvailable(const UnicodeString& filename, const size_t requiredBytes);

   /// @brief Reads the specified binary file.
   /// @param filename The name of the file to be read.
   /// @return <b>BinaryStream*</b> The binary stream that has been read <b>nullptr</b> if the file could not be read.
   static BinaryStream* ReadBinaryFile(const UnicodeString& filename);

   /// @brief Reads the specified text file.
   /// @param filename The name of the file to be read.
   /// @return <b>UnicodeString</b> The lines of text that has been read.
   static UnicodeStringArray ReadTextFile(const UnicodeString& filename);

   /// @brief Writes the specified text file.
   /// @param filename The name of the file to be written.
   /// @param str The text to be written.
   /// @return <b>bool</b> Returns <b>true</b> if the file could be written; otherwise <b>false</b>.
   static bool WriteTextFile(const UnicodeString& filename, const UnicodeString& str);

private:
   static UnicodeString NormalizeFileName(const UnicodeString& targetName);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_FILE_MANAGER_H_INCL__
