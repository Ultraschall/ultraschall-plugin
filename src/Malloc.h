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

/// @file
/// @brief Defines memory allocation functions.

#ifndef __ULTRASCHALL_REAPER_MALLOC_H_INCL__
#define __ULTRASCHALL_REAPER_MALLOC_H_INCL__

#include <cstdlib>

namespace ultraschall { namespace reaper {

/// @brief  Allocates a new instance of the specified type and initializes it with zeros.
/// @tparam T The type of the instance to be allocated.
/// @return A pointer to the allocated instance if the allocation was successful, otherwise nullptr.
template<class T> inline static T* SafeAlloc()
{
   T* ptr = new T();
   if (ptr != nullptr) {
      memset(ptr, 0, sizeof(T));
   }
   return ptr;
}

/// @brief Allocates a new array of the specified type and initializes it with zeros.
/// @tparam T The type of the array to be allocated.
/// @param itemCount The number of items in the array.
/// @return A pointer to the allocated array if the allocation was successful, otherwise nullptr.
template<class T> inline static T* SafeAllocArray(const size_t itemCount)
{
   T* ptr = nullptr;
   if (itemCount > 0) {
      ptr = new T[itemCount]();
      if (ptr != nullptr) {
         memset(ptr, 0, sizeof(T) * itemCount);
      }
   }
   return ptr;
}

/// @brief Deallocates the specified array.
/// @tparam T The type of the array to be deallocated.
/// @param ptr A reference to the pointer to the array to be deallocated.
template<class T> inline static void SafeDeleteArray(T*& ptr)
{
   delete[] ptr;
   ptr = nullptr;
}

/// @brief Deallocates the specified instance.
/// @tparam T The type of the instance to be deallocated.
/// @param ptr A reference to the pointer to the instance to be deallocated.
template<class T> inline static void SafeDelete(T*& ptr)
{
   delete ptr;
   ptr = nullptr;
}

/// @brief Releases the specified shared object.
/// @tparam T The type of the shared object to be released.
/// @param ptr A reference to the pointer to the shared object to be released.
template<class T> inline static void SafeRelease(T*& ptr)
{
   if (ptr != nullptr) {
      ptr->Release();
      ptr = nullptr;
   }
}

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_MALLOC_H_INCL__
