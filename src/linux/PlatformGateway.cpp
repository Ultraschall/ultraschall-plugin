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
#include "PlatformGateway.h"
#include "StringUtilities.h"

#define USE_SWELL_FROM_APP
#include "WDL/swell/swell.h"

namespace ultraschall { namespace reaper {

UnicodeString PlatformGateway::QueryReaperProfilePath()
{
    return "~/.config/REAPER";
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
    if(status == 0) {
        availableSpace = fsi.f_bavail * fsi.f_frsize;
    }

    return availableSpace;
}

UnicodeString PlatformGateway::SelectChaptersFile(
    const UnicodeString& dialogCaption, const UnicodeString& initialDirectory, const UnicodeString& initialFile)
{
    UnicodeString result;

    PRECONDITION_RETURN(dialogCaption.empty() == false, result);
    const char* pCaption = U2H(dialogCaption).c_str();

    const char* pInitialDirectory = nullptr;
    if(initialDirectory.empty() == false) {
        pInitialDirectory = U2H(initialDirectory).c_str();
    }

    const char* pInitialFile = nullptr;
    if(initialFile.empty() == false) {
        pInitialFile = U2H(initialFile).c_str();
    }

    const char* pFileExtensions = "MP4 chapters\0*.chapters.txt\0All files\0*.*\0\0";
    char*       pSelected       = BrowseForFiles(pCaption, pInitialDirectory, pInitialFile, false, pFileExtensions);
    if(pSelected != 0) {
        result = H2U(pSelected);
        free(pSelected);
        pSelected = 0;
    }

    return result;
}

UnicodeString PlatformGateway::SelectAudioFile(
    const UnicodeString& dialogCaption, const UnicodeString& initialDirectory, const UnicodeString& initialFile)
{
    UnicodeString result;

    PRECONDITION_RETURN(dialogCaption.empty() == false, result);
    const char* pCaption = U2H(dialogCaption).c_str();

    const char* pInitialDirectory = nullptr;
    if(initialDirectory.empty() == false) {
        pInitialDirectory = U2H(initialDirectory).c_str();
    }

    const char* pInitialFile = nullptr;
    if(initialFile.empty() == false) {
        pInitialFile = U2H(initialFile).c_str();
    }

    const char* pFileExtensions = "MP3 file\0*.mp3\0All files\0*.*\0\0";
    char*       pSelected       = BrowseForFiles(pCaption, pInitialDirectory, pInitialFile, false, pFileExtensions);
    if(pSelected != 0) {
        result = H2U(pSelected);
        free(pSelected);
        pSelected = 0;
    }

    return result;
}

UnicodeString PlatformGateway::SelectPictureFile(
    const UnicodeString& dialogCaption, const UnicodeString& initialDirectory, const UnicodeString& initialFile)
{
    UnicodeString result;

    PRECONDITION_RETURN(dialogCaption.empty() == false, result);
    const char* pCaption = U2H(dialogCaption).c_str();

    const char* pInitialDirectory = nullptr;
    if(initialDirectory.empty() == false) {
        pInitialDirectory = U2H(initialDirectory).c_str();
    }

    const char* pInitialFile = nullptr;
    if(initialFile.empty() == false) {
        pInitialFile = U2H(initialFile).c_str();
    }

    const char* pFileExtensions = "JPG file\0*.jpg\0PNG file\0*.png\0All files\0*.*\0\0";
    char*       pSelected       = BrowseForFiles(pCaption, pInitialDirectory, pInitialFile, false, pFileExtensions);
    if(pSelected != 0) {
        result = H2U(pSelected);
        free(pSelected);
        pSelected = 0;
    }

    return result;
}

UnicodeString PlatformGateway::SelectChaptersFileName(
    const UnicodeString& dialogCaption, const UnicodeString& initialDirectory, const UnicodeString& initialFile)
{
    UnicodeString result;

    PRECONDITION_RETURN(dialogCaption.empty() == false, result);
    const char* pCaption = U2H(dialogCaption).c_str();

    const char* pInitialDirectory = nullptr;
    if(initialDirectory.empty() == false) {
        pInitialDirectory = U2H(initialDirectory).c_str();
    }

    const char* pInitialFile = nullptr;
    if(initialFile.empty() == false) {
        pInitialFile = U2H(initialFile).c_str();
    }

    const char* pFileExtensions = "MP4 chapters\0*.chapters.txt\0All files\0*.*\0\0";
    char        selected[4096]  = {0};
    if(BrowseForSaveFile(pCaption, pInitialDirectory, pInitialFile, pFileExtensions, selected, 4096)) {
        UnicodeString selectedFile = selected;
        result                     = H2U(selectedFile);
    }

    return result;
}

}} // namespace ultraschall::reaper
