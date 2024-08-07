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

#ifndef __ULTRASCHALL_REAPER_REAPER_ENTRY_POINTS_H_INCL__
#define __ULTRASCHALL_REAPER_REAPER_ENTRY_POINTS_H_INCL__

// disable 'unreferenced formal parameter'
#pragma warning(disable : 4100)
// Include base SDK header
#include <reaper_plugin.h>
#pragma warning(default : 4100)

// This must be included after 'reaper_plugin.h'.
#define REAPERAPI_DECL
#define REAPERAPI_NO_LICE
#define REAPERAPI_MINIMAL
#define REAPERAPI_WANT_GetMainHwnd
#define REAPERAPI_WANT_plugin_register
#define REAPERAPI_WANT_GetAppVersion
#define REAPERAPI_WANT_GetExePath
#define REAPERAPI_WANT_GetProjectPath
#define REAPERAPI_WANT_GetProjectPathEx
#define REAPERAPI_WANT_EnumProjects
#define REAPERAPI_WANT_format_timestr_pos
#define REAPERAPI_WANT_parse_timestr
#define REAPERAPI_WANT_PreventUIRefresh
#define REAPERAPI_WANT_CountProjectMarkers
#define REAPERAPI_WANT_EnumProjectMarkers
#define REAPERAPI_WANT_EnumProjectMarkers2
#define REAPERAPI_WANT_EnumProjectMarkers3
#define REAPERAPI_WANT_AddProjectMarker2
#define REAPERAPI_WANT_SetProjectMarker3
#define REAPERAPI_WANT_DeleteProjectMarker
#define REAPERAPI_WANT_GetPlayStateEx
#define REAPERAPI_WANT_GetCursorPositionEx
#define REAPERAPI_WANT_GetPlayPositionEx
#define REAPERAPI_WANT_GetLastMarkerAndCurRegion
#define REAPERAPI_WANT_DeleteProjectMarkerByIndex
#define REAPERAPI_WANT_GetSetProjectNotes
#define REAPERAPI_WANT_SetProjExtState
#define REAPERAPI_WANT_GetProjExtState
#define REAPERAPI_WANT_EnumProjExtState
#define REAPERAPI_WANT_HasExtState
#define REAPERAPI_WANT_SetExtState
#define REAPERAPI_WANT_GetExtState
#define REAPERAPI_WANT_DeleteExtState
#define REAPERAPI_WANT_GetMediaItem
#define REAPERAPI_WANT_GetMediaItemInfo_Value
#define REAPERAPI_WANT_GetSetProjectInfo_String

namespace reaper_api {
#include "reaper_plugin_functions.h"
} // namespace reaper_api

namespace ultraschall { namespace reaper {

/// @brief The ReaperEntryPoints class provides functions for setting up the REAPER entry points.
class ReaperEntryPoints
{
public:
   /// @brief The REAPER plugin instance.
   static REAPER_PLUGIN_HINSTANCE instance_;

   /// @brief Initializes the REAPER entry points.
   /// @param instance The REAPER plugin instance.
   /// @param pPluginInfo The plugin information.
   /// @return <b>true</b> if the entry points could be set up, <b>false</b> otherwise.
   static bool Setup(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo);

private:
   static bool LoadEntryPoints(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_REAPER_ENTRY_POINTS_H_INCL__
