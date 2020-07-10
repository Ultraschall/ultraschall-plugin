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
  ${LIBZ_INCLUDE_PATH}
  ${LIBCURL_INCLUDE_PATH}
  ${LIBTAG_INCLUDE_PATH}
  ${LIBSWELL_INCLUDE_PATH}
  ${REAPER_INCLUDE_PATH}
)

set(COMMON_INCLUDES
  Application.h
  BinaryStream.h
  ChapterImage.h
  ChapterTag.h
  ChapterUrl.h
  Common.h
  CustomAction.h
  CustomActionFactory.h
  CustomActionManager.h
  FileDialog.h
  FileManager.h
  Globals.h
  HttpClient.h
  HttpRequest.h
  HttpResponse.h
  ICommand.h
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
  UpdateHandler.h
  UnicodeString.h
)

set(COMMON_SOURCES
  Application.cpp
  BinaryStream.cpp
  CustomAction.cpp
  CustomActionFactory.cpp
  CustomActionManager.cpp
  FileManager.cpp
  HttpClient.cpp
  HttpRequest.cpp
  HttpResponse.cpp
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
  UpdateHandler.cpp
  UnicodeString.cpp
  reaper_ultraschall.cpp
)

set(EXTRA_INCLUDES)
set(EXTRA_SOURCES ${LIBZ_SOURCE_PATH}/contrib/minizip/ioapi.c ${LIBZ_SOURCE_PATH}/contrib/minizip/unzip.c)

set(PLATFORM_INCLUDES FileDialog.h Platform.h)
set(PLATFORM_SOURCES
  ${ULTRASCHALL_TARGET_SYSTEM}/FileDialog.cpp
  ${ULTRASCHALL_TARGET_SYSTEM}/Platform.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR})

if(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "win32")
  set(EXTRA_SOURCES ${EXTRA_SOURCES} reaper_ultraschall.rc)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  set(EXTRA_LIBRARIES version.lib ws2_32.lib crypt32.lib wldap32.lib mfplat.lib mf.lib mfuuid.lib shlwapi.lib comctl32.lib comdlg32.lib rpcrt4.lib)
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "macos")
  add_compile_options(-mmacosx-version-min=10.11)
  set_source_files_properties(macos/Platform.cpp macos/FileDialog.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
  set(EXTRA_LIBRARIES "-framework AppKit" "-framework Carbon" "-framework IOKit" "-framework Security")
  set(COCKOS_SOURCES
    ${LIBSWELL_SOURCE_PATH}/swell.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-ini.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-misc.mm
    ${LIBSWELL_SOURCE_PATH}/swell-wnd.mm
    ${LIBSWELL_SOURCE_PATH}/swell-gdi.mm
    ${LIBSWELL_SOURCE_PATH}/swell-dlg.mm
    ${LIBSWELL_SOURCE_PATH}/swell-kb.mm
    ${LIBSWELL_SOURCE_PATH}/swell-menu.mm
  )
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "linux")
  include_directories(${LIBGTK3_INCLUDE_PATH})
  set(EXTRA_LIBRARIES ${LIBGTK3_LIBRARY_PATH})
  set(COCKOS_SOURCES
    ${LIBSWELL_SOURCE_PATH}/swell.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-ini.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-misc-generic.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-wnd-generic.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-gdi-generic.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-dlg-generic.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-kb-generic.cpp
    ${LIBSWELL_SOURCE_PATH}/swell-menu-generic.cpp
  )
endif()

message(STATUS "COMMON_INCLUDES   = ${COMMON_INCLUDES}")
message(STATUS "COMMON_SOURCES    = ${COMMON_SOURCES}")
message(STATUS "PLATFORM_INCLUDES = ${PLATFORM_INCLUDES}")
message(STATUS "PLATFORM_SOURCES  = ${PLATFORM_SOURCES}")
message(STATUS "EXTRA_INCLUDES    = ${EXTRA_INCLUDES}")
message(STATUS "EXTRA_SOURCES     = ${EXTRA_SOURCES}")
message(STATUS "COCKOS_INCLUDES   = ${COCKOS_INCLUDES}")
message(STATUS "COCKOS_SOURCES    = ${COCKOS_SOURCES}")

source_group("Header Files"   FILES ${COMMON_INCLUDES} ${PLATFORM_INCLUDES})
source_group("Source Files"   FILES ${COMMON_SOURCES} ${PLATFORM_SOURCES})
source_group("External Files" FILES ${EXTRA_SOURCES} ${EXTERNAL_SOURCES} ${COCKOS_SOURCES})

add_library(reaper_ultraschall SHARED
  ${COMMON_INCLUDES}
  ${COMMON_SOURCES}
  ${PLATFORM_INCLUDES}
  ${PLATFORM_SOURCES}
  ${EXTRA_INCLUDES}
  ${EXTRA_SOURCES}
  ${COCKOS_SOURCES}
)

add_dependencies(reaper_ultraschall zlibstatic)
add_dependencies(reaper_ultraschall libcurl)
add_dependencies(reaper_ultraschall tag)

target_link_libraries(reaper_ultraschall
  ${LIBZ_LIBRARY_PATH}
  ${LIBCURL_LIBRARY_PATH}
  ${LIBTAG_LIBRARY_PATH}
  ${EXTRA_LIBRARIES}
)

set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")
