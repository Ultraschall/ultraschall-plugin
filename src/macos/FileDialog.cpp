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

#include "FileDialog.h"
#include "ReaperGateway.h"
#include "StringUtilities.h"

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

namespace ultraschall { namespace reaper {

FileDialog::FileDialog(const UnicodeString& caption, const UnicodeString& initialDirectory) {}

FileDialog::~FileDialog() {}

UnicodeString FileDialog::SelectChaptersFile()
{
    UnicodeString result;

    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
        fileDialog.canChooseFiles          = YES;
        fileDialog.canChooseDirectories    = NO;
        fileDialog.canCreateDirectories    = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.title                   = [NSString stringWithUTF8String:caption_.c_str()];
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

UnicodeString FileDialog::SelectAudioFile()
{
    UnicodeString result;

    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
        fileDialog.canChooseFiles          = YES;
        fileDialog.canChooseDirectories    = NO;
        fileDialog.canCreateDirectories    = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.title                   = [NSString stringWithUTF8String:caption_.c_str()];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        // FIXME: Disable mp4 due to bug #13
        //if([fileDialog runModalForTypes:[[NSArray alloc] initWithObjects:@"mp3", @"mp4", @"m4a", nil]]
        if([fileDialog runModalForTypes:[[NSArray alloc] initWithObjects:@"mp3", nil]]
           == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
        {
            result = [[fileDialog URL] fileSystemRepresentation];
        }

        fileDialog = nil;
    }

    return result;
}

UnicodeString FileDialog::SelectPictureFile()
{
    UnicodeString result;

    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
        fileDialog.canChooseFiles          = YES;
        fileDialog.canChooseDirectories    = NO;
        fileDialog.canCreateDirectories    = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.title                   = [NSString stringWithUTF8String:caption_.c_str()];
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

UnicodeString FileDialog::SelectDirectory()
{
    UnicodeString result;

    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        fileDialog.canCreateDirectories    = YES;
        fileDialog.canChooseDirectories    = YES;
        fileDialog.canChooseFiles          = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.prompt                  = @"Select";
        fileDialog.title                   = [NSString stringWithUTF8String:caption_.c_str()];

        NSString* initialPath = [NSString stringWithUTF8String:initialDirectory_.c_str()];
        if([fileDialog runModalForDirectory:initialPath file:nil types:nil] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
        {
            result = [[fileDialog URL] fileSystemRepresentation];
        }

        fileDialog = nil;
    }

    return result;
}

UnicodeString FileDialog::ChooseChaptersFileName()
{
    UnicodeString result;
    
    NSSavePanel* fileDialog = [NSSavePanel savePanel];
    if(nil != fileDialog)
    {
        fileDialog.allowedFileTypes = [[NSArray alloc] initWithObjects:@"chapters.txt", @"mp4chaps", @"txt", nil];
        fileDialog.allowsOtherFileTypes = NO;
        fileDialog.canCreateDirectories    = YES;
        fileDialog.title                   = [NSString stringWithUTF8String:caption_.c_str()];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        if([fileDialog runModal] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
        {
            result = [[fileDialog URL] fileSystemRepresentation];
        }
        
        fileDialog = nil;
    }
    
    return result;
}

}} // namespace ultraschall::reaper
