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

#ifndef __ULTRASCHALL_REAPER_PLATFORM_GATEWAY_H_INCL__
#define __ULTRASCHALL_REAPER_PLATFORM_GATEWAY_H_INCL__

#include "Common.h"

#ifdef _MSC_VER
   /// @brief Swaps the bytes of a 16-bit value.
   #define FastByteSwap16(x) _byteswap_ushort(x)
   /// @brief Swaps the bytes of a 32-bit value.
   #define FastByteSwap32(x) _byteswap_ulong(x)
   /// @brief Swaps the bytes of a 64-bit value.
   #define FastByteSwap64(x) _byteswap_uint64(x)
#else
   /// @brief Swaps the bytes of a 16-bit value.
   #define FastByteSwap16(x) __builtin_bswap16(x)
   /// @brief Swaps the bytes of a 32-bit value.
   #define FastByteSwap32(x) __builtin_bswap32(x)
   /// @brief Swaps the bytes of a 64-bit value.
   #define FastByteSwap64(x) __builtin_bswap64(x)
#endif // #ifdef _MSC_VER

namespace ultraschall { namespace reaper {

/// @brief The PlatformGateway class provides functions for platform-specific operations.
class PlatformGateway
{
public:
   /// @brief Returns the path to the REAPER profile.
   /// @return The path to the REAPER profile.
   static UnicodeString QueryReaperProfilePath();

   /// @brief Returns the current platform's path separator.
   /// @return The current platform's path separator.
   static UnicodeChar QueryPathSeparator();

   /// @brief Returns the currently available disk space (checked against the user's quota).
   /// @param directory The directory for which the available disk space will be checked.
   /// @return The currently available disk space.
   static size_t QueryAvailableDiskSpace(const UnicodeString& directory);

   /// @brief Selects a chapter file for opening.
   /// @param dialogCaption The caption of the dialog.
   /// @param initialDirectory The initial directory.
   /// @param initialFile The initial file name.
   /// @return The selected file name.
   static UnicodeString
   SelectChaptersFile(const UnicodeString& dialogCaption, const UnicodeString& initialDirectory = "", const UnicodeString& initialFile = "");

   /// @brief Selects an audio file for opening.
   /// @param dialogCaption The caption of the dialog.
   /// @param initialDirectory The initial directory.
   /// @param initialFile The initial file name.
   /// @return The selected file name.
   static UnicodeString SelectAudioFile(const UnicodeString& dialogCaption, const UnicodeString& initialDirectory = "", const UnicodeString& initialFile = "");

   /// @brief Selects a picture file for opening.
   /// @param dialogCaption The caption of the dialog.
   /// @param initialDirectory The initial directory.
   /// @param initialFile The initial file name.
   /// @return The selected file name.
   static UnicodeString
   SelectPictureFile(const UnicodeString& dialogCaption, const UnicodeString& initialDirectory = "", const UnicodeString& initialFile = "");

   /// @brief Selects a chapter file for saving.
   /// @param dialogCaption The caption of the dialog.
   /// @param initialDirectory The initial directory.
   /// @param initialFile The initial file name.
   /// @return The selected file name.
   static UnicodeString SelectChaptersFileName(const UnicodeString& dialogCaption, const UnicodeString& initialDirectory, const UnicodeString& initialFile);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_PLATFORM_GATEWAY_H_INCL__
