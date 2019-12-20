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

#include "TagWriterFactory.h"
#include "ID3V2Writer.h"
#include "MP4CHAPSWriter.h"
#include "StringUtilities.h"
#include "FileManager.h"

namespace ultraschall { namespace reaper {

ITagWriter* TagWriterFactory::Create(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);
    PRECONDITION_RETURN(targetName.length() > 4, 0);

    ITagWriter*                  tagWriter  = nullptr;
    const FileManager::FILE_TYPE targetType = FileManager::QueryFileType(targetName);
    if(targetType == FileManager::FILE_TYPE::MP4CHAPS)
    {
        tagWriter = new MP4CHAPSWriter();
    }
    else if(targetType == FileManager::FILE_TYPE::MP3)
    {
        tagWriter = new ID3V2Writer();
    }
    else
    {
        tagWriter = nullptr;
    }

    return tagWriter;
}

}} // namespace ultraschall::reaper
