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

#ifndef __ULTRASCHALL_REAPER_ID3V2_CONTEXT_H_INCL__
#define __ULTRASCHALL_REAPER_ID3V2_CONTEXT_H_INCL__

#include "Common.h"

#include "taglib_include.h"

namespace ultraschall { namespace reaper { 

class ID3V2Context
{
public:
    ID3V2Context(const UnicodeString& targetName);
    virtual ~ID3V2Context();

    inline bool IsValid() const;

    inline taglib_mp3::File*  Target();
    inline taglib_id3v2::Tag* Tags();
    inline uint32_t           Duration() const;

private:
    taglib_mp3::File*  target_ = nullptr;
    taglib_id3v2::Tag* tags_   = nullptr;
    uint32_t duration_ = -1;

    ID3V2Context(const ID3V2Context&) = delete;
    ID3V2Context& operator=(const ID3V2Context&) = delete;
};

inline bool ID3V2Context::IsValid() const
{
    return (target_ != nullptr) && (tags_ != nullptr);
}

inline taglib_mp3::File* ID3V2Context::Target()
{
    return target_;
}

inline taglib_id3v2::Tag* ID3V2Context::Tags()
{
    return tags_;
}

inline uint32_t ID3V2Context::Duration() const 
{
  return duration_;
}

}} // namespace ultraschall::reaper::id3v2

#endif // #ifndef __ULTRASCHALL_REAPER_ID3V2_CONTEXT_H_INCL__
