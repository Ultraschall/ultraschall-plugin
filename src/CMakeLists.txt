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

set(REAPER_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../include/reaper)

add_definitions(-DWDL_NO_DEFINE_MINMAX)

include_directories(
  ${LIBCURL_INCLUDE_PATH}
  ${LIBTAG_INCLUDE_PATH}
  ${LIBSWELL_INCLUDE_PATH}
  ${REAPER_INCLUDE_PATH}
)

set(COMMON_INCLUDES
  Application.h
  BinaryStream.h
  ChapterTag.h
  Common.h
  CustomAction.h
  CustomActionFactory.h
  CustomActionManager.h
  FileManager.h
  Globals.h
  HttpClient.h
  ICustomAction.h
  ID3V2.h
  ID3V2Context.h
  ID3V2Writer.h
  InsertChapterMarkersAction.h
  InsertMediaPropertiesAction.h
  ITagWriter.h
  SharedObject.h
  Malloc.h
  Picture.h
  ProfileProperties.h
  ReaperProject.h
  ReaperEntryPoints.h
  ReaperGateway.h
  resource.h
  SaveChapterMarkersAction.h
  SaveChapterMarkersToProjectAction.h
  SequentialStream.h
  ServiceStatus.h
  StringUtilities.h
  SystemProperties.h
  taglib_include.h
  TagWriterFactory.h
  Notification.h
  NotificationClass.h
  NotificationQueue.h
  NotificationStore.h
  UnicodeString.h
  UpdateHandler.h
  Version.h
)

set(COMMON_SOURCES
  Application.cpp
  BinaryStream.cpp
  CustomAction.cpp
  CustomActionFactory.cpp
  CustomActionManager.cpp
  FileManager.cpp
  HttpClient.cpp
  ID3V2.cpp
  ID3V2Context.cpp
  ID3V2Writer.cpp
  InsertChapterMarkersAction.cpp
  InsertMediaPropertiesAction.cpp
  Picture.cpp
  ProfileProperties.cpp
  ReaperProject.cpp
  ReaperEntryPoints.cpp
  ReaperGateway.cpp
  SaveChapterMarkersAction.cpp
  SaveChapterMarkersToProjectAction.cpp
  SequentialStream.cpp
  StringUtilities.cpp
  SystemProperties.cpp
  TagWriterFactory.cpp
  Notification.cpp
  NotificationQueue.cpp
  NotificationStore.cpp
  UnicodeString.cpp
  UpdateHandler.cpp
  Version.cpp
  reaper_ultraschall.cpp
)

set(PLATFORM_INCLUDES PlatformGateway.h)
set(PLATFORM_SOURCES ${ULTRASCHALL_TARGET_SYSTEM}/PlatformGateway.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR})

if(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "windows")
  set(EXTRA_SOURCES ${EXTRA_SOURCES} reaper_ultraschall.rc)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  set(EXTRA_LIBRARIES version.lib ws2_32.lib crypt32.lib wldap32.lib mfplat.lib mf.lib mfuuid.lib shlwapi.lib comctl32.lib comdlg32.lib rpcrt4.lib)
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "macos")
  add_definitions(-DSWELL_PROVIDED_BY_APP)
  set_source_files_properties(macos/PlatformGateway.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
  set(EXTRA_LIBRARIES "-framework AppKit" "-framework CoreFoundation" "-framework Security" "-framework SystemConfiguration")
  set(COCKOS_SOURCES ${LIBSWELL_SOURCE_PATH}/swell-modstub.mm)
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "linux")
  add_definitions(-DSWELL_PROVIDED_BY_APP)
  set(COCKOS_SOURCES ${LIBSWELL_SOURCE_PATH}/swell-modstub-generic.cpp)
endif()

source_group("Header Files"   FILES ${COMMON_INCLUDES} ${PLATFORM_INCLUDES})
source_group("Source Files"   FILES ${COMMON_SOURCES} ${PLATFORM_SOURCES})
source_group("External Files" FILES ${EXTRA_SOURCES} ${EXTERNAL_SOURCES} ${COCKOS_SOURCES})

add_library(reaper_ultraschall SHARED
  ${COMMON_INCLUDES}
  ${COMMON_SOURCES}
  ${PLATFORM_INCLUDES}
  ${PLATFORM_SOURCES}
  ${EXTRA_SOURCES}
  ${COCKOS_SOURCES}
)

add_dependencies(reaper_ultraschall tag)

if (ULTRASCHALL_TARGET_SYSTEM STREQUAL "linux")
  set(OPENSSL_USE_STATIC_LIBS TRUE)
  find_package(OpenSSL REQUIRED)
  target_link_libraries(reaper_ultraschall OpenSSL::Crypto)
endif()

target_link_libraries(reaper_ultraschall
  ${LIBZ_LIBRARY_PATH}
  ${LIBCURL_LIBRARY_PATH}
  ${LIBTAG_LIBRARY_PATH}
  ${LIBSSL_LIBRARY_PATH}
  ${EXTRA_LIBRARIES}
)

set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")
