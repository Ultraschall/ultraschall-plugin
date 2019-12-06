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

#ifdef min
#undef min
#endif // #ifdef min
#ifdef max
#undef max
#endif // #ifdef max

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#include "FileManager.h"
#include "Platform.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

UnicodeString Platform::QueryUserDataDirectory()
{
    UnicodeString directory;

    NSString* userHomeDirectory = NSHomeDirectory();
    directory                   = [userHomeDirectory UTF8String];

    return directory;
}

UnicodeString Platform::QueryProgramFilesDirectory()
{
    UnicodeString directory;

    NSURL* applicationSupportDirectory =
        [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory inDomains:NSSystemDomainMask]
            firstObject];
    directory = [applicationSupportDirectory fileSystemRepresentation];

    return directory;
}

UnicodeChar Platform::QueryPathSeparator()
{
    return '/';
}

bool Platform::QueryFileExists(const UnicodeString& path)
{
    PRECONDITION_RETURN(path.empty() == false, false);

    bool fileExists = false;

    NSFileManager* fileManager = [NSFileManager defaultManager];
    fileExists                 = [fileManager fileExistsAtPath:[NSString stringWithUTF8String:path.c_str()]] == YES;

    return fileExists;
}

UnicodeString Platform::AppendPath(const UnicodeString& prefix, const UnicodeString& appendix)
{
    return prefix + QueryPathSeparator() + appendix;
}

}} // namespace ultraschall::reaper
