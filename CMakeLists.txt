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

cmake_minimum_required(VERSION 3.24)
cmake_policy(SET CMP0091 NEW)

project(reaper_ultraschall
  VERSION 5.1.0
  DESCRIPTION "Podcasting extensions for REAPER"
  LANGUAGES C CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS        OFF)
  set(CMAKE_CXX_STANDARD          20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

if(WIN32)
    set(ULTRASCHALL_TARGET_SYSTEM "windows")
elseif(APPLE)
    set(ULTRASCHALL_TARGET_SYSTEM "macos")
elseif(UNIX)
  execute_process(COMMAND uname RESULT_VARIABLE UNAME_RESULT OUTPUT_VARIABLE UNAME_OUTPUT OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(UNAME_RESULT EQUAL 0)
    if(${UNAME_OUTPUT} MATCHES "[L|l]inux")
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    else()
      message(STATUS "Unsupported platform: " ${UNAME_OUTPUT})
      message(FATAL_ERROR "Supported platforms are Linux, Windows and macOS")
    endif()
  else()
    message(FATAL_ERROR "Failed to run uname, result: ${UNAME_RESULT}")
  endif()
endif()

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOCS "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
  # set input and output files
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/scripts/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  # request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Doxygen build started")

  # note the option ALL which allows to build the docs together with the application
  add_custom_target(doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)

else (DOXYGEN_FOUND)
  message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

set(CMAKE_POSITION_INDEPENDENT_CODE ON  CACHE INTERNAL "")
set(CMAKE_WARN_DEPRECATED           OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS               OFF CACHE INTERNAL "")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

set(LIBZ_VERSION_TAG    "v1.3")
set(LIBCURL_VERSION_TAG "curl-8_4_0")
set(LIBTAG_VERSION_TAG  "v1.11.1")

include(cmake/${ULTRASCHALL_TARGET_SYSTEM}.cmake)

add_subdirectory(src)
