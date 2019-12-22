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

#ifndef __ULTRASCHALL_REAPER_PICTURE_H_INCL__
#define __ULTRASCHALL_REAPER_PICTURE_H_INCL__

#include "BinaryStream.h"

namespace ultraschall { namespace reaper {

class Picture
{
public:
    enum class FORMAT { JPEG, PNG, UNKNOWN_PICTURE, MAX_FORMAT = UNKNOWN_PICTURE };

    static FORMAT Format(const uint8_t* data, const size_t dataSize);
    static FORMAT Format(const BinaryStream* pStream);
    static FORMAT Format(const UnicodeString& filename);

    static UnicodeString FormatString(const uint8_t* data, const size_t dataSize);
    static UnicodeString FormatString(const BinaryStream* pStream);
    static UnicodeString FormatString(const UnicodeString& filename);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_PICTURE_H_INCL__
