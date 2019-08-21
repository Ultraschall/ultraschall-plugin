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

#include "ReaperGateway.h"
#include "StringUtilities.h"
#include "UIFileDialog.h"

namespace ultraschall { namespace reaper {

UIFileDialog::UIFileDialog(const UnicodeString& caption, const UnicodeString& initialDirectory) {}

UIFileDialog::~UIFileDialog() {}

UnicodeString UIFileDialog::BrowseForChapters()
{
    return BrowseForFile("MP4 chapters|*.chapters.txt|MP4 chapters|*.mp4chaps");
}

UnicodeString UIFileDialog::BrowseForAudio()
{
    return BrowseForFile("MP3 file|*.mp3|MP4 file|*.mp4|M4A file|*.m4a");
}

UnicodeString UIFileDialog::BrowseForPicture()
{
    return BrowseForFile("JPG file|*.jpg|PNG file|*.png");
}

UnicodeString UIFileDialog::BrowseForDirectory()
{
    UnicodeString result;

    return result;
}

UnicodeString UIFileDialog::BrowseForFile(const UnicodeString& fileExtensions)
{
    PRECONDITION_RETURN(fileExtensions.empty() == false, "");

    UnicodeString result;

    return result;
}

}} // namespace ultraschall::reaper

