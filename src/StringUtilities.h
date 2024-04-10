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

#ifndef __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__
#define __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

#define _MAKE_TEXT(str) #str
#define MAKE_TEXT(str)  _MAKE_TEXT(str)

/// @brief Split a string into an array of strings.
/// @param input The input string.
/// @param delimiter The delimiter character.
/// @return An array of strings.
UnicodeStringArray UnicodeStringTokenize(const UnicodeString& input, const char delimiter);

/// @brief Removes leading whitespaces from a string.
/// @param str The string to be processed.
/// @return The processed string.
void UnicodeStringTrimLeft(UnicodeString& str);

/// @brief Removes trailing whitespaces from a string.
/// @param str The string to be processed.
/// @return The processed string.
void UnicodeStringTrimRight(UnicodeString& str);

/// @brief Removes leading and trailing whitespaces from a string.
/// @param str The string to be processed.
/// @return The processed string.
void UnicodeStringTrim(UnicodeString& str);

/// @brief Copies a string and removes leading whitespaces.
/// @param str The string to be processed.
/// @return The processed string.
UnicodeString UnicodeStringCopyTrimLeft(UnicodeString str);

/// @brief Copies a string and removes trailing whitespaces.
/// @param str The string to be processed.
/// @return The processed string.
UnicodeString UnicodeStringCopyTrimRight(UnicodeString str);

/// @brief Copies a string and removes leading and trailing whitespaces.
/// @param str The string to be processed.
/// @return The processed string.
UnicodeString UnicodeStringCopyTrim(UnicodeString str);

/// @brief Replaces all occurrences of a substring in a string.
/// @param str The string to be processed.
/// @param source The substring to be replaced.
/// @param target The replacement substring.
void UnicodeStringReplace(UnicodeString& str, const UnicodeString& source, const UnicodeString& target);

/// @brief Converts a string to an integer.
/// @param str The string to be converted.
/// @return The converted integer.
int UnicodeStringToInt(const UnicodeString& str);

/// @brief Converts an integer to a string.
/// @param value The integer to be converted.
/// @return The converted string.
UnicodeString UnicodeStringFromInt(const int value);

/// @brief Converts a string to lower case.
/// @param str The string to be converted.
/// @return The converted string.
UnicodeString StringLowercase(const UnicodeString& str);

/// @brief Converts a string to upper case.
/// @param str The string to be converted.
/// @return The converted string.
UnicodeString StringUppercase(const UnicodeString& str);

/// @brief Converts a timestamp to a string.
/// @param milliseconds The timestamp to be converted.
/// @param roundSeconds Determines whether the seconds should be rounded.
/// @return The converted string.
UnicodeString MillisecondsToString(const uint32_t milliseconds, const bool roundSeconds = false);

/// @brief Converts a string to a timestamp.
/// @param str The string to be converted.
/// @return The converted timestamp.
uint32_t StringToMilliseconds(const UnicodeString& str);

/// @brief Converts a timestamp to a string.
/// @param seconds The timestamp to be converted.
/// @param roundSeconds Determines whether the seconds should be rounded.
/// @return The converted string.
UnicodeString SecondsToString(const double seconds, const bool roundSeconds = false);

/// @brief Converts a string to a timestamp.
/// @param str The string to be converted.
/// @return The converted timestamp.
double StringToSeconds(const UnicodeString& str);

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__
