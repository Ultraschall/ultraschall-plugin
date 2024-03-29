################################################################################
#
# Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

add_compile_options(-Wno-deprecated-declarations)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-delete-non-virtual-dtor")

include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "$ENV{HOME}/.config/REAPER/UserPlugins")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/artifacts")

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
  set(LIBZ_INCLUDE_PATH ${ZLIB_INCLUDE_DIRS})
  set(LIBZ_LIBRARY_PATH ${ZLIB_LIBRARIES})
endif()

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    set(LIBSSL_LIBRARY_PATH ${OPENSSL_LIBRARIES})
else()
    message(FATAL_ERROR "Fatal: Can't find openssl development package.")
endif()

find_package(CURL REQUIRED)
if(CURL_FOUND)
  set(LIBCURL_INCLUDE_PATH ${CURL_INCLUDE_DIRS})
  set(LIBCURL_LIBRARY_PATH ${CURL_LIBRARIES})
endif()

set(CURRENT_EXTERNAL_PROJECT libtag)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring...")
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/taglib/taglib.git
  GIT_TAG ${LIBTAG_VERSION_TAG}
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBTAG_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR} ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/toolkit ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg/id3v2 ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg/id3v2/frames)
  set(LIBTAG_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/taglib/libtag.a)
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(BUILD_TESTS            OFF)
  set(BUILD_EXAMPLES         OFF)
  set(BUILD_BINDINGS         OFF)
  add_subdirectory(${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure swell
set(CURRENT_EXTERNAL_PROJECT libswell)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring...")
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/justinfrankel/WDL.git
  GIT_TAG origin/main
  SOURCE_SUBDIR wdl
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBSWELL_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR})
  set(LIBSWELL_SOURCE_PATH  ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/WDL/swell)
endif()
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")
