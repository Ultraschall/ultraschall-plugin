////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#include "Application.h"
#include "ServiceStatus.h"
#include "UIMessageSupervisor.h"

#include "CustomActionManager.h"

#include "InsertChapterMarkersAction.h"
#include "InsertMediaPropertiesAction.h"
#include "SaveChapterMarkersAction.h"
#include "SaveChapterMarkersToProjectAction.h"
#include "SystemProperties.h"

#include "ReaperEntryPoints.h"

extern "C" {
REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE handle, reaper_plugin_info_t* pPluginInfo)
{
    if(pPluginInfo != 0)
    {
        static bool started = false;
        if(false == started)
        {
            if(ultraschall::reaper::ReaperEntryPoints::Setup(handle, pPluginInfo) == true)
            {
                if(ultraschall::reaper::QuerySetPluginVersion() == true)
                {
                    ultraschall::reaper::Application& application = ultraschall::reaper::Application::Instance();
                    if(ServiceSucceeded(application.Start((intptr_t)handle)))
                    {
                        application.RegisterCustomAction<ultraschall::reaper::InsertChapterMarkersAction>();
                        application.RegisterCustomAction<ultraschall::reaper::SaveChapterMarkersAction>();
                        application.RegisterCustomAction<ultraschall::reaper::SaveChapterMarkersToProjectAction>();
                        application.RegisterCustomAction<ultraschall::reaper::InsertMediaPropertiesAction>();
                        started = true;
                    }
                }
            }
            else
            {
                ultraschall::reaper::UIMessageSupervisor supervisor;
                supervisor.RegisterFatalError("Ultraschall failed to load!");
                supervisor.RegisterFatalError(
                    "You are trying to load a version of REAPER that is not compatible to Ultraschall 3.");
            }
        }

        return 1;
    }
    else
    {
        static bool stopped = false;
        if(false == stopped)
        {
            ultraschall::reaper::Application& application = ultraschall::reaper::Application::Instance();
            application.Stop();

            stopped = true;
        }

        return 0;
    }
}
}

#ifdef _WIN32

#ifdef _DEBUG
static void PrintDllPath()
{
    HMODULE hModule = NULL;
    BOOL    fStatus  = GetModuleHandleEx(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCSTR)&ReaperPluginEntry, &hModule);
    if(fStatus != FALSE)
    {
        CHAR szModulePath[MAX_PATH] = {0};
        DWORD dwModulePathLength = GetModuleFileName(hModule, szModulePath, MAX_PATH * sizeof(CHAR));
        if(dwModulePathLength > 0)
        {
            MessageBox(NULL, szModulePath, "Ultraschall", MB_OK);
        }
    }
}
#else  // #ifdef _DEBUG
void PrintDllPath() {}
#endif // #ifdef _DEBUG

//#define ULTRASCHALL_STARTUP_DIAGNOSITICS 1

BOOL APIENTRY DllMain(HMODULE, ULONG ul_reason_for_call, LPVOID)
{
    switch(ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
#ifdef ULTRASCHALL_STARTUP_DIAGNOSITICS
          PrintDllPath();
#endif // #ifdef ULTRASCHALL_STARTUP_DIAGNOSITICS
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
#else  // #ifdef _WIN32
#include "WDL/swell/swell-dlggen.h"
#include "reaper_ultraschall.rc_mac_dlg"
#undef BEGIN
#undef END
#include "WDL/swell/swell-menugen.h"
#include "reaper_ultraschall.rc_mac_menu"
#endif // #ifdef _WIN32
