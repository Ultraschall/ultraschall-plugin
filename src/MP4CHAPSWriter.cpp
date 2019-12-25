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

#include "MP4CHAPSWriter.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

bool MP4CHAPSWriter::Start(const UnicodeString& targetName) 
{
  return false;
}

void MP4CHAPSWriter::Stop(const bool commit)
{}

bool MP4CHAPSWriter::InsertProperties(const UnicodeString& targetName, const UnicodeStringDictionary& mediaData)
{
    return true;
}

bool MP4CHAPSWriter::InsertCoverImage(const UnicodeString& targetName, const UnicodeString& coverImage)
{
    return true;
}

bool MP4CHAPSWriter::InsertChapterMarkers(const UnicodeString& targetName, const ChapterTagArray& chapterMarkers)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(chapterMarkers.empty() == false, false);

    bool success = false;

    return success;
}

}} // namespace ultraschall::reaper
