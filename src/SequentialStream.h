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

#ifndef __ULTRASCHALL_REAPER_SEQUENTIAL_STREAM_H_INCL__
#define __ULTRASCHALL_REAPER_SEQUENTIAL_STREAM_H_INCL__

#include "Common.h"
#include "SharedObject.h"

namespace ultraschall { namespace reaper {

/// @brief The SequentialStream class implements a simple sequential stream.
class SequentialStream : public SharedObject
{
public:
   /// @brief A constant that represents an invalid data size.
   static const size_t INVALID_DATA_SIZE = -1;

   /// @brief Creates a new SequentialStream instance.
   SequentialStream();

   /// @brief Returns the current size of the data.
   /// @return The current size of the data.
   size_t DataSize() const;

   /// @brief Returns the current data.
   /// @return A pointer to the current data, or nullptr if no data is available.
   const uint8_t* Data() const;

   /// @brief Writes the specified data to the stream.
   /// @param buffer The buffer that contains the data to be written.
   /// @param bufferSize The size of the buffer.
   /// @return <b>true</b> if the data was written successfully, <b>false</b> otherwise.
   bool Write(const uint8_t* buffer, const size_t bufferSize);

   /// @brief Reads the specified data from the stream.
   /// @param buffer The buffer that receives the data.
   /// @param bufferSize The size of the buffer.
   /// @return The number of bytes that were read.
   size_t Read(uint8_t* buffer, const size_t bufferSize);

protected:
   virtual ~SequentialStream();

private:
   static const size_t DEFAULT_CHUNK_SIZE = 4096;

   size_t writePosition_                  = 0;
   size_t readPosition_                   = 0;
   size_t dataSize_                       = INVALID_DATA_SIZE;
   uint8_t* data_                         = nullptr;
};

}} // namespace ultraschall::reaper

#endif // #ifdef __ULTRASCHALL_REAPER_SEQUENTIAL_STREAM_H_INCL__
