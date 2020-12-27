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

#include "SequentialStream.h"
#include <cstring>
#include <zlib.h>

namespace ultraschall { namespace reaper {

SequentialStream::SequentialStream() : dataSize_(DEFAULT_CHUNK_SIZE), data_(new uint8_t[DEFAULT_CHUNK_SIZE]) {}

SequentialStream::~SequentialStream()
{
    writePosition_ = 0;
    readPosition_  = 0;
    dataSize_      = INVALID_DATA_SIZE;
    SafeDeleteArray(data_);
}

size_t SequentialStream::DataSize() const
{
    // return dataSize_;
    return writePosition_;
}

const uint8_t* SequentialStream::Data() const
{
    return data_;
}

bool SequentialStream::Write(const uint8_t* buffer, const size_t bufferSize)
{
    PRECONDITION_RETURN(data_ != nullptr, false);
    PRECONDITION_RETURN(buffer != nullptr, false);
    PRECONDITION_RETURN(bufferSize > 0, false);
    PRECONDITION_RETURN(bufferSize <= DEFAULT_CHUNK_SIZE, false);

    bool spaceAvailable = true;

    if((writePosition_ + bufferSize) > dataSize_)
    {
        uint8_t* pData = data_;
        data_          = new uint8_t[dataSize_ + DEFAULT_CHUNK_SIZE]();
        if(data_ != nullptr)
        {
            memmove(data_, pData, dataSize_);
            dataSize_ += DEFAULT_CHUNK_SIZE;

            SafeDeleteArray(pData);
        }
        else
        {
            spaceAvailable = false;
        }
    }

    if(true == spaceAvailable)
    {
        const size_t itemSize = sizeof(uint8_t);
        memmove(&data_[writePosition_], buffer, bufferSize * itemSize);
        writePosition_ += bufferSize;
    }

    return spaceAvailable;
}

size_t SequentialStream::Read(uint8_t* buffer, const size_t bufferSize)
{
    PRECONDITION_RETURN(data_ != nullptr, 0);
    PRECONDITION_RETURN(buffer != nullptr, 0);
    PRECONDITION_RETURN(bufferSize > 0, 0);
    PRECONDITION_RETURN(readPosition_ < (writePosition_ - bufferSize), 0);

    size_t result = 0;

    const size_t chunkSize = ((readPosition_ + bufferSize) < dataSize_) ? bufferSize : (dataSize_ - readPosition_);
    if(chunkSize > 0)
    {
        memmove(buffer, &data_[readPosition_], chunkSize);
        readPosition_ += chunkSize;
    }

    return result;
}

}} // namespace ultraschall::reaper
