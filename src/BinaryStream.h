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

#ifndef __ULTRASCHALL_REAPER_BINARY_STREAM_H_INCL__
#define __ULTRASCHALL_REAPER_BINARY_STREAM_H_INCL__

#include "Common.h"
#include "SharedObject.h"

namespace ultraschall { namespace reaper {

/// @brief The BinaryStream class implements a simple binary stream.
class BinaryStream : public SharedObject
{
public:
   /// @brief A constant that specifies an invalid data size.
   static const size_t INVALID_DATA_SIZE = -1;

   /// @brief The constructor initializes a new BinaryStream instance.
   /// @param dataSize Specifies the initial size of the binary stream.
   BinaryStream(const size_t dataSize);

   /// @brief Returns the data size of the binary stream.
   /// @return <b>size_t</b> The data size of the binary stream if the data size is valid; otherwise <b>INVALID_DATA_SIZE</b>.
   size_t DataSize() const;

   /// @brief Returns the data of the binary stream.
   /// @return <b>const uint8_t*</b> The data of the binary stream if the data size is valid; otherwise <b>nullptr</b>.
   const uint8_t* Data() const;

   /// @brief Writes the specified data to the binary stream.
   /// @param offset Specifies the offset in the binary stream.
   /// @param buffer  Specifies the data to be written.
   /// @param bufferSize Specifies the size of the data to be written.
   /// @return <b>bool</b> Returns <b>true</b> if the data has been written successfully; otherwise <b>false</b>.
   bool Write(const size_t offset, const uint8_t* buffer, const size_t bufferSize);

   /// @brief Reads the specified data from the binary stream.
   /// @param offset Specifies the offset in the binary stream.
   /// @param buffer Specifies the buffer to store the data.
   /// @param bufferSize Specifies the size of the buffer.
   /// @return <b>bool</b> Returns <b>true</b> if the data has been read successfully; otherwise <b>false</b>.
   bool Read(const size_t offset, uint8_t* buffer, const size_t bufferSize);

protected:
   virtual ~BinaryStream();

private:
   size_t dataSize_ = INVALID_DATA_SIZE;
   uint8_t* data_   = nullptr;
};

}} // namespace ultraschall::reaper

#endif // #ifdef __ULTRASCHALL_REAPER_BINARY_STREAM_H_INCL__
