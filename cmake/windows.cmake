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

include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "$ENV{USERPROFILE}/AppData/Roaming/REAPER/UserPlugins")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/artifacts")

set(CURRENT_EXTERNAL_PROJECT libz)
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/madler/zlib.git
  GIT_TAG ${LIBZ_VERSION_TAG}
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBZ_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR} ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/contrib/minizip)
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(LIBZ_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/zlibstaticd.lib)
  else()
    set(LIBZ_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/zlibstatic.lib)
  endif()
  set(LIBZ_SOURCE_PATH  ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR})
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(SKIP_INSTALL_ALL       ON)
  add_subdirectory(${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()

set(CURRENT_EXTERNAL_PROJECT libcurl)
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG ${LIBCURL_VERSION_TAG}
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBCURL_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/include)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBCURL_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/lib/libcurl-d.lib)
  else()
    set(LIBCURL_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/lib/libcurl.lib)
  endif()
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(BUILD_CURL_EXE      OFF CACHE INTERNAL "")
  set(BUILD_TESTING       OFF CACHE INTERNAL "")
  set(BUILD_BINDINGS      OFF CACHE INTERNAL "")
  option(HTTP_ONLY "disables all protocols except HTTP (This overrides all CURL_DISABLE_* options)" ON)
  option(CURL_USE_SCHANNEL "Enable Windows native SSL/TLS" ON)
  add_subdirectory(${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()

set(CURRENT_EXTERNAL_PROJECT libtag)
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/taglib/taglib.git
  GIT_TAG ${LIBTAG_VERSION_TAG}
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBTAG_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR} ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/toolkit ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg/id3v2 ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg/id3v2/frames)
  set(LIBTAG_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/taglib/tag.lib)
  set(BUILD_SHARED_LIBS_SAVE ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS      OFF)
  set(BUILD_TESTS            OFF)
  set(BUILD_EXAMPLES         OFF)
  set(BUILD_BINDINGS         OFF)
  add_subdirectory(${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR})
  set(BUILD_SHARED_LIBS      ${BUILD_SHARED_LIBS_SAVE})
endif()

set(CURRENT_EXTERNAL_PROJECT libswell)
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
