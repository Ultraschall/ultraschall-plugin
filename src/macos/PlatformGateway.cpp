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

#include <sys/statvfs.h>

#include "PlatformGateway.h"

namespace ultraschall { namespace reaper {

UnicodeString PlatformGateway::QueryReaperProfilePath()
{
    UnicodeString directory;

    NSString* userHomeDirectory = NSHomeDirectory();
    directory                   = [userHomeDirectory UTF8String];

    return directory + "REAPER";
}

UnicodeChar PlatformGateway::QueryPathSeparator()
{
    return '/';
}

size_t PlatformGateway::QueryAvailableDiskSpace(const UnicodeString& directory)
{
    PRECONDITION_RETURN(directory.empty() == false, -1);

    size_t availableSpace = -1;

    struct statvfs fsi    = {0};
    const int      status = statvfs(directory.c_str(), &fsi);
    if(status == 0)
    {
        availableSpace = fsi.f_bavail * fsi.f_frsize;
    }

    return availableSpace;
}

UnicodeString PlatformGateway::SelectChaptersFile(
    const UnicodeString& dialogCaption, const UnicodeString&, const UnicodeString&)
{
    UnicodeString result;

    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
        fileDialog.canChooseFiles          = YES;
        fileDialog.canChooseDirectories    = NO;
        fileDialog.canCreateDirectories    = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.title                   = [NSString stringWithUTF8String:dialogCaption.c_str()];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        if([fileDialog runModalForTypes:[[NSArray alloc] initWithObjects:@"chapters.txt", @"mp4chaps", @"txt", nil]]
           == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
        {
            result = [[fileDialog URL] fileSystemRepresentation];
        }

        fileDialog = nil;
    }

    return result;
}

UnicodeString PlatformGateway::SelectAudioFile(
    const UnicodeString& dialogCaption, const UnicodeString&, const UnicodeString&)
{
    UnicodeString result;

    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
        fileDialog.canChooseFiles          = YES;
        fileDialog.canChooseDirectories    = NO;
        fileDialog.canCreateDirectories    = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.title                   = [NSString stringWithUTF8String:dialogCaption.c_str()];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        if([fileDialog runModalForTypes:[[NSArray alloc] initWithObjects:@"mp3", nil]] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
        {
            result = [[fileDialog URL] fileSystemRepresentation];
        }

        fileDialog = nil;
    }

    return result;
}

UnicodeString PlatformGateway::SelectPictureFile(
    const UnicodeString& dialogCaption, const UnicodeString&, const UnicodeString&)
{
    UnicodeString result;

    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
        fileDialog.canChooseFiles          = YES;
        fileDialog.canChooseDirectories    = NO;
        fileDialog.canCreateDirectories    = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.title                   = [NSString stringWithUTF8String:dialogCaption.c_str()];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        if([fileDialog runModalForTypes:[[NSArray alloc] initWithObjects:@"png", @"jpg", @"jpeg", nil]]
           == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
        {
            result = [[fileDialog URL] fileSystemRepresentation];
        }

        fileDialog = nil;
    }

    return result;
}

UnicodeString PlatformGateway::SelectChaptersFileName(
    const UnicodeString& dialogCaption, const UnicodeString& initialDirectory, const UnicodeString& initialFile)
{
    UnicodeString result;

    NSSavePanel* fileDialog = [NSSavePanel savePanel];
    if(nil != fileDialog)
    {
        fileDialog.allowedFileTypes     = [[NSArray alloc] initWithObjects:@"chapters.txt", @"mp4chaps", @"txt", nil];
        fileDialog.allowsOtherFileTypes = NO;
        fileDialog.canCreateDirectories = YES;
        fileDialog.title                = [NSString stringWithUTF8String:dialogCaption.c_str()];

        NSString* initialDirectoryParam = nil;
        if(initialDirectory.empty() == false)
        {
            initialDirectoryParam = [NSString stringWithUTF8String:initialDirectory.c_str()];
        }

        NSString* initialFileParam = nil;
        if(initialFile.empty() == false)
        {
            initialFileParam = [NSString stringWithUTF8String:initialFile.c_str()];
        }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        if([fileDialog runModalForDirectory:initialDirectoryParam file:initialFileParam] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
        {
            result = [[fileDialog URL] fileSystemRepresentation];
        }

        fileDialog = nil;
    }

    return result;
}

}} // namespace ultraschall::reaper
