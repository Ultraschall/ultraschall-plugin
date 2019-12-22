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

#include "Application.h"
#include "CustomAction.h"
#include "FileManager.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "UINotificationStore.h"
#include "UpdateCheck.h"

namespace ultraschall { namespace reaper {

Application::Application() {}

Application::~Application() {}

Application& Application::Instance()
{
    static Application self;
    return self;
}

ServiceStatus Application::Start(intptr_t handle)
{
    ServiceStatus                         status = SERVICE_FAILURE;
    std::lock_guard<std::recursive_mutex> cs(lock_);
    if(handle_ == 0)
    {
        handle_ = handle;
        UpdateCheck();
        status = SERVICE_SUCCESS;
    }

    return status;
}

void Application::Stop() {}

bool Application::OnCustomAction(const int32_t id)
{
    PRECONDITION_RETURN(CustomAction::IsValidCustomActionId(id) != false, false);

    bool executed = false;

    CustomActionManager& manager       = CustomActionManager::Instance();
    ICustomAction*       pCustomAction = 0;
    ServiceStatus        status        = manager.LookupCustomAction(id, pCustomAction);
    if(ServiceSucceeded(status) && (pCustomAction != 0))
    {
        pCustomAction->Execute();
        executed = true;

        SafeRelease(pCustomAction);
    }

    return executed;
}

}} // namespace ultraschall::reaper
