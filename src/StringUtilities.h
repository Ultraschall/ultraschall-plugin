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
#define MAKE_TEXT(str) _MAKE_TEXT(str)

UnicodeStringArray UnicodeStringTokenize(const UnicodeString& input, const char delimiter);

void UnicodeStringTrimLeft(UnicodeString& str);
void UnicodeStringTrimRight(UnicodeString& str);
void UnicodeStringTrim(UnicodeString& str);

UnicodeString UnicodeStringCopyTrimLeft(UnicodeString str);
UnicodeString UnicodeStringCopyTrimRight(UnicodeString str);
UnicodeString UnicodeStringCopyTrim(UnicodeString str);

void UnicodeStringReplace(UnicodeString& str, const UnicodeString& source, const UnicodeString& target);

int UnicodeStringToInt(const UnicodeString& str);
UnicodeString UnicodeStringFromInt(const int value);

UnicodeString StringLowercase(const UnicodeString& str);
UnicodeString StringUppercase(const UnicodeString& str);

UnicodeString MillisecondsToString(const uint32_t milliseconds, const bool roundSeconds = false);
uint32_t StringToMilliseconds(const UnicodeString& str);
UnicodeString SecondsToString(const double seconds, const bool roundSeconds = false);
double StringToSeconds(const UnicodeString& str);

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__
