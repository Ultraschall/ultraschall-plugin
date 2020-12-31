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

# configure zlib
set(CURRENT_EXTERNAL_PROJECT libz)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring...")
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/madler/zlib.git
  GIT_TAG v1.2.11
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBZ_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR} ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/contrib/minizip)
  set(LIBZ_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/libz.a)
  set(LIBZ_SOURCE_PATH  ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR})
  message(STATUS "LIBZ_INCLUDE_PATH = ${LIBZ_INCLUDE_PATH}")
  message(STATUS "LIBZ_LIBRARY_PATH = ${LIBZ_LIBRARY_PATH}")
  message(STATUS "LIBZ_SOURCE_PATH  = ${LIBZ_SOURCE_PATH}")
  set(SKIP_INSTALL_ALL ON CACHE INTERNAL  "")
  add_subdirectory(${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR})
endif()
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure curl
set(CURRENT_EXTERNAL_PROJECT libcurl)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring...")
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG curl-7_63_0
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBCURL_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/include)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBCURL_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/lib/libcurl-d.a)
  else()
    set(LIBCURL_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/lib/libcurl.a)
  endif()
  message(STATUS "LIBCURL_INCLUDE_PATH = ${LIBCURL_INCLUDE_PATH}")
  message(STATUS "LIBCURL_LIBRARY_PATH = ${LIBCURL_LIBRARY_PATH}")
  set(BUILD_CURL_EXE      OFF CACHE INTERNAL "")
  set(BUILD_BINDINGS      OFF CACHE INTERNAL "")
  set(BUILD_TESTING       OFF CACHE INTERNAL "")
  set(CMAKE_USE_DARWINSSL OFF CACHE INTERNAL "")
  set(CMAKE_USE_LIBSSH2   OFF CACHE INTERNAL "")
  set(CMAKE_USE_OPENSSL   ON  CACHE INTERNAL "")
  set(CMAKE_USE_WINSSL    OFF CACHE INTERNAL "")
  set(CURL_CA_PATH        none CACHE INTERNAL "")
  set(CURL_DISABLE_LDAP   ON  CACHE INTERNAL "")
  set(CURL_DISABLE_LDAPS  ON  CACHE INTERNAL "")
  set(ENABLE_IPV6         ON  CACHE INTERNAL "")
  set(ENABLE_MANUAL       OFF CACHE INTERNAL "")
  set(HTTP_ONLY           ON  CACHE INTERNAL "")
  add_subdirectory(${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR})
endif()
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

set(CURRENT_EXTERNAL_PROJECT libtag)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring...")
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/taglib/taglib.git
  GIT_TAG v1.11.1
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBTAG_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR} ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/toolkit ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg/id3v2 ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/taglib/mpeg/id3v2/frames)
  set(LIBTAG_LIBRARY_PATH ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR}/taglib/libtag.a)
  message(STATUS "LIBTAG_INCLUDE_PATH = ${LIBTAG_INCLUDE_PATH}")
  message(STATUS "LIBTAG_LIBRARY_PATH = ${LIBTAG_LIBRARY_PATH}")
  message(STATUS "LIBTAG_SOURCE_PATH  = ${LIBTAG_SOURCE_PATH}")
  set(BUILD_TESTS    OFF CACHE INTERNAL "")
  set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
  set(BUILD_BINDINGS OFF CACHE INTERNAL "")
  add_subdirectory(${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR} ${${CURRENT_EXTERNAL_PROJECT}_BINARY_DIR})
endif()
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure swell
set(CURRENT_EXTERNAL_PROJECT libswell)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring...")
FetchContent_Declare(${CURRENT_EXTERNAL_PROJECT}
  GIT_REPOSITORY https://github.com/justinfrankel/WDL.git
  SOURCE_SUBDIR wdl
)
FetchContent_GetProperties(${CURRENT_EXTERNAL_PROJECT})
if(NOT ${CURRENT_EXTERNAL_PROJECT}_POPULATED)
  FetchContent_Populate(${CURRENT_EXTERNAL_PROJECT})
  set(LIBSWELL_INCLUDE_PATH ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR})
  set(LIBSWELL_SOURCE_PATH  ${${CURRENT_EXTERNAL_PROJECT}_SOURCE_DIR}/WDL/swell)
  message(STATUS "LIBSWELL_INCLUDE_PATH = ${LIBSWELL_INCLUDE_PATH}")
  message(STATUS "LIBSWELL_SOURCE_PATH  = ${LIBSWELL_SOURCE_PATH}")
endif()
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")
