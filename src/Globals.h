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

#ifndef __ULTRASCHALL_REAPER_GLOBALS_H_INCL__
#define __ULTRASCHALL_REAPER_GLOBALS_H_INCL__

namespace ultraschall { namespace reaper {

struct Globals
{
    static constexpr size_t MAX_CHAPTER_TITLE_LENGTH = 62;

    static constexpr const double INVALID_MARKER_POSITION = -1;

    static constexpr const int DEFAULT_EDIT_MARKER_COLOR = 0x010000ff;

    static constexpr const int DEFAULT_CHAPTER_MARKER_COLOR = 0x00000000;

    static constexpr const size_t MIN_CHAPTER_MARKER_LINE_LENGTH = 5;  
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_GLOBALS_H_INCL__
