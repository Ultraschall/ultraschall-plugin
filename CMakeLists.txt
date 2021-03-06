################################################################################
#
# Copyright (c) The Ultraschall Project (https://ultraschall.fm)
#
# The MIT License (MIT)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

cmake_minimum_required(VERSION 3.19)

project(reaper_ultraschall
  VERSION 4.1.0
  DESCRIPTION "Podcasting extensions for REAPER"
  LANGUAGES C CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if(WIN32)
    set(ULTRASCHALL_TARGET_SYSTEM "win32")
elseif(APPLE)
    set(ULTRASCHALL_TARGET_SYSTEM "macos")
elseif(UNIX)
  execute_process(COMMAND uname -a RESULT_VARIABLE UNAME_RESULT OUTPUT_VARIABLE UNAME_OUTPUT OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(UNAME_RESULT EQUAL 0)
    if(${UNAME_OUTPUT} MATCHES "[A|a]rch")
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    elseif(${UNAME_OUTPUT} MATCHES "[U|u]buntu")
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    elseif(${UNAME_OUTPUT} MATCHES "Linux")
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    elseif(${UNAME_OUTPUT} MATCHES "[M|m]icrosoft") # WSL
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    elseif(${UNAME_OUTPUT} MATCHES "[A|a]zure") # Azure DevOps
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    else()
      message(STATUS "Unsupported platform: " ${UNAME_OUTPUT})
      message(FATAL_ERROR "Supported platforms are Windows, macOS, Arch Linux and Ubuntu Linux")
    endif()
  else()
    message(FATAL_ERROR "Failed to run uname, result: ${UNAME_RESULT}")
  endif()
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON  CACHE INTERNAL  "")
set(CMAKE_WARN_DEPRECATED           OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS               OFF CACHE INTERNAL "")

message(STATUS "ULTRASCHALL_TARGET_SYSTEM = " ${ULTRASCHALL_TARGET_SYSTEM})
include(cmake/${ULTRASCHALL_TARGET_SYSTEM}.cmake)

# message(STATUS "LIBZ_INCLUDE_PATH     = ${LIBZ_INCLUDE_PATH}")
# message(STATUS "LIBZ_LIBRARY_PATH     = ${LIBZ_LIBRARY_PATH}")
# message(STATUS "LIBZ_SOURCE_PATH      = ${LIBZ_SOURCE_PATH}")
# message(STATUS "LIBCURL_INCLUDE_PATH  = ${LIBCURL_INCLUDE_PATH}")
# message(STATUS "LIBCURL_LIBRARY_PATH  = ${LIBCURL_LIBRARY_PATH}")
# message(STATUS "LIBTAG_INCLUDE_PATH   = ${LIBTAG_INCLUDE_PATH}")
# message(STATUS "LIBTAG_LIBRARY_PATH   = ${LIBTAG_LIBRARY_PATH}")
# message(STATUS "LIBSWELL_INCLUDE_PATH = ${LIBSWELL_INCLUDE_PATH}")
# message(STATUS "LIBSWELL_SOURCE_PATH  = ${LIBSWELL_SOURCE_PATH}")
# message(STATUS "LIBSSL_LIBRARY_PATH   = ${LIBSSL_LIBRARY_PATH}")

add_subdirectory(src)
