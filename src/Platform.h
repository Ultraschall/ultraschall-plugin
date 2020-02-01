////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#ifndef __ULTRASCHALL_REAPER_PLATFORM_H_INCL__
#define __ULTRASCHALL_REAPER_PLATFORM_H_INCL__

#include "Common.h"

#ifdef _MSC_VER
#define FastByteSwap16(x) _byteswap_ushort(x)
#define FastByteSwap32(x) _byteswap_ulong(x)
#define FastByteSwap64(x) _byteswap_uint64(x)
#else
#define FastByteSwap16(x) __builtin_bswap16(x)
#define FastByteSwap32(x) __builtin_bswap32(x)
#define FastByteSwap64(x) __builtin_bswap64(x)
#endif // #ifdef _MSC_VER

namespace ultraschall {
namespace reaper {

class Platform {
public:
  static UnicodeChar QueryPathSeparator();
  static size_t QueryAvailableDiskSpace(const UnicodeString &directory);
};

} // namespace reaper
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_REAPER_PLATFORM_H_INCL__
