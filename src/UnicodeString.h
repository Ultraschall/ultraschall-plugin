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

#ifndef __ULTRASCHALL_REAPER_UNICODE_STRING_H_INCL__
#define __ULTRASCHALL_REAPER_UNICODE_STRING_H_INCL__

#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace ultraschall { namespace reaper {

/// @brief The definition of a UTF-8 character.
typedef char UnicodeChar;

/// @brief The definition of a UTF-16 character.
typedef char16_t WideUnicodeChar;

/// @brief The definition of a UTF-8 string.
typedef std::string UnicodeString;

/// @brief The definition of a UTF-16 string.
typedef std::u16string WideUnicodeString;

/// @brief The definition of a UTF-8 string stream.
typedef std::stringstream UnicodeStringStream;

/// @brief The definition of a UTF-16 string stream.
typedef std::basic_stringstream<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>> WideUnicodeStringStream;

/// @brief The definition of a UTF-8 string array.
typedef std::vector<UnicodeString> UnicodeStringArray;

/// @brief The definition of a UTF-8 string dictionary.
typedef std::map<UnicodeString, UnicodeString> UnicodeStringDictionary;

/// @brief The definition of a UTF-16 string array.
typedef std::vector<WideUnicodeString> WideUnicodeStringArray;

/// @brief The definition of a UTF-16 string dictionary.
typedef std::map<WideUnicodeString, WideUnicodeString> WideUnicodeStringDictionary;

/// @brief A enumeration that defines the character encoding.
typedef enum
{
   /// @brief The UTF-8 character encoding.
   UTF8,

   /// @brief The UTF-16 character encoding.
   UTF16
} CHAR_ENCODING;

/// @brief An enumeration that defines the byte order for UTF-16 strings
typedef enum
{
   /// @brief The default UTF-16 byte order.
   NO_UTF16_BOM      = 0,

   /// @brief The UTF-16 byte order for little-endian systems.
   WITH_UTF16_BOM_LE = 1,

   /// @brief The UTF-16 byte order for big-endian systems.
   WITH_UTF16_BOM_BE = 2
} UTF16_BOM_SPEC;

/// @brief The UTF-16 byte order mark for little-endian systems.
static const char16_t* UTF16_BOM_LE = u"\xfffe"; // intel

/// @brief The UTF-16 byte order mark for big-endian systems.
static const char16_t* UTF16_BOM_BE = u"\xfeff";

/// @brief Converts an UTF-8 string to a UTF-16 string.
/// @param unicodeString The UTF-8 string to be converted.
/// @param bomSpec The byte order mark specification.
/// @return The converted UTF-16 string.
WideUnicodeString UnicodeStringToWideUnicodeString(const UnicodeString& unicodeString, const UTF16_BOM_SPEC bomSpec = NO_UTF16_BOM);

/// @brief An enumeration that defines the byte order for UTF-8 strings
typedef enum
{
   /// @brief Byte order mark is not used.
   NO_UTF8_BOM   = 0,

   /// @brief Byte order mark is used.
   WITH_UTF8_BOM = 1
} UTF8_BOM_SPEC;

/// @brief The UTF-8 byte order mark.
static const char* UTF8_BOM = "\xef\xbb\xbf";

/// @brief Converts an UTF-16 string to a UTF-8 string.
/// @param wideUnicodeString The UTF-16 string to be converted.
/// @param bomSpec The byte order mark specification.
/// @return The converted UTF-8 string.
UnicodeString WideUnicodeStringToUnicodeString(const WideUnicodeString& wideUnicodeString, const UTF8_BOM_SPEC bomSpec = NO_UTF8_BOM);

/// @brief Converts an native host system string to a UTF-8 string.
/// @param hostString The native host system string to be converted.
/// @param bomSpec The byte order mark specification.
/// @return The converted UTF-16 string.
UnicodeString HostStringToUnicodeString(const std::string& hostString, const UTF8_BOM_SPEC bomSpec = NO_UTF8_BOM);

/// @brief Converts an native host system string to a UTF-16 string.
/// @param hostString  The native host system string to be converted.
/// @param bomSpec The byte order mark specification.
/// @return The converted UTF-16 string.
WideUnicodeString HostStringToWideUnicodeString(const std::string& hostString, const UTF16_BOM_SPEC bomSpec = NO_UTF16_BOM);

/// @brief Converts a UTF-8 string to a native host system string.
/// @param unicodeString The UTF-8 string to be converted.
/// @return The converted native host system string.
std::string UnicodeStringToHostString(const UnicodeString& unicodeString);

/// @brief Converts a UTF-16 string to a native host system string.
/// @param wideUnicodeString The UTF-16 string to be converted.
/// @return The converted native host system string.
std::string WideUnicodeStringToHostString(const WideUnicodeString& wideUnicodeString);

#define H2U(a)  HostStringToUnicodeString((a))
#define H2WU(a) HostStringToWideUnicodeString((a))

#define U2H(a)  UnicodeStringToHostString((a))
#define WU2H(a) WideUnicodeStringToHostString((a))

#define U2WU(a) UnicodeStringToWideUnicodeString((a))
#define WU2U(a) WideUnicodeStringToUnicodeString((a))

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_UNICODE_STRING_H_INCL__
