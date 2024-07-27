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

#ifndef __ULTRASCHALL_REAPER_PICTURE_H_INCL__
#define __ULTRASCHALL_REAPER_PICTURE_H_INCL__

#include "BinaryStream.h"

namespace ultraschall { namespace reaper {

/// @brief The Picture class provides functions for working with pictures.
class Picture
{
public:
   /// @brief The FORMAT enumeration represents the supported picture formats.
   enum class FORMAT
   {
      /// @brief The picture format is JPEG.
      JPEG,
      /// @brief The picture format is PNG.
      PNG,
      /// @brief The picture format is unknown.
      UNKNOWN_PICTURE,
      /// @brief The picture format is unsupported.
      MAX_FORMAT = UNKNOWN_PICTURE
   };

   /// @brief Returns the format of the specified picture data.
   /// @param data The picture data.
   /// @param dataSize The size of the picture data.
   /// @return The format of the picture data.
   static FORMAT Format(const uint8_t* data, const size_t dataSize);

   /// @brief Returns the format of the specified picture data.
   /// @param pStream The picture data.
   /// @return The format of the picture data.
   static FORMAT Format(const BinaryStream* pStream);

   /// @brief Returns the format of the specified picture file based on the file extension.
   /// @param filename The picture file.
   /// @return The format of the picture file.
   static FORMAT Format(const UnicodeString& filename);

   /// @brief Returns the format of the specified picture data as a string.
   /// @param data The picture data.
   /// @param dataSize The size of the picture data.
   /// @return The format of the picture data.
   static UnicodeString FormatString(const uint8_t* data, const size_t dataSize);

   /// @brief Returns the format of the specified picture data as a string
   /// @param pStream The picture data.
   /// @return The format of the picture data.
   static UnicodeString FormatString(const BinaryStream* pStream);

   /// @brief Returns the format of the specified picture file as a string based on the file extension.
   /// @param filename The picture file.
   /// @return The format of the picture file.
   static UnicodeString FormatString(const UnicodeString& filename);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_PICTURE_H_INCL__
