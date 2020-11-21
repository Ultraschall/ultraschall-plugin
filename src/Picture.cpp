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

#include "Picture.h"
#include "FileManager.h"
#include "PlatformGateway.h"

namespace ultraschall { namespace reaper {

Picture::FORMAT Picture::Format(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, FORMAT::UNKNOWN_PICTURE);
    PRECONDITION_RETURN(dataSize > 0, FORMAT::UNKNOWN_PICTURE);

    FORMAT format = FORMAT::UNKNOWN_PICTURE;
    if(dataSize >= 2)
    {
        if((data[0] == 0xff) && (data[1] == 0xd8))
        {
            format = FORMAT::JPEG;
        }

        if(dataSize >= 8)
        {
            if((data[0] == 0x89) && (data[1] == 0x50) && (data[2] == 0x4e) && (data[3] == 0x47))
            {
                format = FORMAT::PNG;
            }
        }
    }

    return format;
}

Picture::FORMAT Picture::Format(const BinaryStream* pStream)
{
    PRECONDITION_RETURN(pStream != nullptr, FORMAT::UNKNOWN_PICTURE);

    return Format(pStream->Data(), pStream->DataSize());
}

Picture::FORMAT Picture::Format(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, FORMAT::UNKNOWN_PICTURE);

    FORMAT        format  = FORMAT::UNKNOWN_PICTURE;
    BinaryStream* pStream = FileManager::ReadBinaryFile(filename);
    if(pStream != nullptr)
    {
        format = Format(pStream);

        SafeRelease(pStream);
    }

    return format;
}

UnicodeString Picture::FormatString(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != nullptr, UnicodeString());
    PRECONDITION_RETURN(dataSize > 0, UnicodeString());

    UnicodeString formatString;

    const FORMAT pictureFormat = Format(data, dataSize);
    switch(pictureFormat)
    {
        case FORMAT::JPEG:
        {
            formatString = "image/jpeg";
            break;
        }
        case FORMAT::PNG:
        {
            formatString = "image/png";
            break;
        }
        default:
        {
            break;
        }
    }

    return formatString;
}

UnicodeString Picture::FormatString(const BinaryStream* pStream)
{
    PRECONDITION_RETURN(pStream != nullptr, UnicodeString());

    return FormatString(pStream->Data(), pStream->DataSize());
}

UnicodeString Picture::FormatString(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, UnicodeString());

    UnicodeString formatString;
    BinaryStream* pStream = FileManager::ReadBinaryFile(filename);
    if(pStream != nullptr)
    {
        formatString = FormatString(pStream);
        SafeRelease(pStream);
    }

    return formatString;
}

}} // namespace ultraschall::reaper
