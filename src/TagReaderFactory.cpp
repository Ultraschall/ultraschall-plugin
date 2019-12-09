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

#include "TagReaderFactory.h"
#include "ID3V2Reader.h"
#include "ISOBMFFReader.h"
#include "MP4CHAPSReader.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

ITagReader* TagReaderFactory::Create(const UnicodeString& sourceName)
{
    PRECONDITION_RETURN(sourceName.empty() == false, 0);
    PRECONDITION_RETURN(sourceName.length() > 4, 0);

    ITagReader*       tagReader  = nullptr;
    const SOURCE_TYPE sourceType = FindFileType(sourceName);
    if(sourceType == SOURCE_TYPE::MP4CHAPS_SOURCE)
    {
        tagReader = new MP4CHAPSReader();
    }
    else if(sourceType == SOURCE_TYPE::MP3_SOURCE)
    {
        tagReader = new ID3V2Reader();
    }
    else if(sourceType == SOURCE_TYPE::MP4_SOURCE)
    {
        tagReader = new ISOBMFFReader();
    }
    else
    {
        tagReader = nullptr;
    }

    return tagReader;
}

UnicodeString TagReaderFactory::NormalizeSourceName(const UnicodeString& sourceName)
{
    UnicodeString firstStage  = sourceName;
    UnicodeString secondStage = UnicodeStringTrimRight(firstStage);
    return StringLowercase(secondStage);
}

TagReaderFactory::SOURCE_TYPE TagReaderFactory::FindFileType(const UnicodeString& sourceName)
{
    PRECONDITION_RETURN(sourceName.empty() == false, SOURCE_TYPE::INVALID_SOURCE_TYPE);

    SOURCE_TYPE         type             = SOURCE_TYPE::INVALID_SOURCE_TYPE;
    const UnicodeString cookedSourceName = NormalizeSourceName(sourceName);
    const size_t        extensionOffset  = sourceName.rfind(".");
    if(extensionOffset != UnicodeString::npos)
    {
        const UnicodeString fileExtension
            = sourceName.substr(extensionOffset + 1, sourceName.length() - extensionOffset);
        if(fileExtension.empty() == false)
        {
            if((fileExtension == "txt") || (fileExtension == "mp4chaps"))
            {
                type = SOURCE_TYPE::MP4CHAPS_SOURCE;
            }
            else if(fileExtension == "mp3")
            {
                type = SOURCE_TYPE::MP3_SOURCE;
            }
            else if((fileExtension == "mp4") || (fileExtension == "m4a"))
            {
                type = SOURCE_TYPE::MP4_SOURCE;
            }
            else
            {
                type = SOURCE_TYPE::INVALID_SOURCE_TYPE;
            }
        }
    }
    return type;
}

}} // namespace ultraschall::reaper
