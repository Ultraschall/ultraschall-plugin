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

#ifndef __ULTRASCHALL_REAPER_COMMON_H_INCL__
#define __ULTRASCHALL_REAPER_COMMON_H_INCL__

#ifdef __GNUC__
   #undef min
   #undef max
#endif // #ifdef __GNUC__

#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <deque>
#include <map>
#include <string>
#include <vector>

#include <algorithm>
#include <cmath>
#include <functional>

#include <fstream>
#include <iomanip>
#include <sstream>

#include <atomic>
#include <mutex>

#include <chrono>
#include <ctime>

#include "Globals.h"
#include "Malloc.h"
#include "ServiceStatus.h"
#include "SharedObject.h"
#include "UnicodeString.h"

#define PRECONDITION(a) \
   {                    \
      if ((a) == 0) {   \
         return;        \
      }                 \
   }

#define PRECONDITION_RETURN(a, b) \
   {                              \
      if ((a) == 0) {             \
         return (b);              \
      }                           \
   }

#define ULTRASCHALL_VERSION "5.1.0"

#endif // #ifndef __ULTRASCHALL_REAPER_COMMON_H_INCL__
