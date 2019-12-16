////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#include <sys/statvfs.h>

#include "Common.h"
#include "Platform.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

UnicodeChar Platform::QueryPathSeparator()
{
    return '/';
}

size_t Platform::QueryAvailableDiskSpace(const UnicodeString& directory)
{
    PRECONDITION_RETURN(directory.empty() == false, -1);

    size_t availableSpace = -1;

    struct statvfs fsi = {0};
    const int status = statvfs(directory.c_str(), &fsi);
    if(status == 0)
    {
        availableSpace = fsi.f_bavail * fsi.f_frsize;
    }

    return availableSpace;
}

}} // namespace ultraschall::reaper
