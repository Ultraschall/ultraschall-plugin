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

#ifndef __ULTRASCHALL_REAPER_UPDATE_CHECK_H_INCL__
#define __ULTRASCHALL_REAPER_UPDATE_CHECK_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

class UpdateHandler
{
public:
    static bool IsUpdateCheckRequired();
    static void Check();

private:
    static const UnicodeString CHECK_ENABLED_PROFILE_NAME;
    static const UnicodeString CHECK_ENABLED_SECTION_NAME;
    static const UnicodeString CHECK_ENABLED_VALUE_NAME;

    static const UnicodeString LAST_CHECKPOINT_PROFILE_NAME;
    static const UnicodeString LAST_CHECKPOINT_SECTION_NAME;
    static const UnicodeString LAST_CHECKPOINT_VALUE_NAME;

    static const double        ONE_DAY_IN_SECONDS;

    static bool   WriteLastUpdateTimestamp(const double timestamp);
    static double ReadLastUpdateTimestamp();

    static size_t ReceiveDataHandler(void* pData, size_t dataSize, size_t itemSize, void* pStream);

    static double QueryCurrentTimeAsSeconds();
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_UPDATE_CHECK_H_INCL__
