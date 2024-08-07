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

#ifndef __ULTRASCHALL_REAPER_IUNKNOWN_H_INCL__
#define __ULTRASCHALL_REAPER_IUNKNOWN_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

/// @brief This interface provides the basic functionality for reference counting.
class SharedObject
{
public:
   /// @brief Constructor
   SharedObject() : refCount_(1) {}

   /// @brief Increments the reference count.
   /// @return The new reference count.
   const uint32_t AddRef()
   {
      return ++refCount_;
   }

   // @brief Decrements the reference count.
   /// @return The new reference count.
   const uint32_t Release()
   {
      const uint32_t refCount = --refCount_;
      if (refCount == 0) {
         delete this;
      }

      return refCount;
   }

protected:
   virtual ~SharedObject() {}

private:
   std::atomic<uint32_t> refCount_;
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_IUNKNOWN_H_INCL__
