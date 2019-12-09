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

#ifndef __ULTRASCHALL_REAPER_UI_NOTIFICATION_STORE_H_INCL__
#define __ULTRASCHALL_REAPER_UI_NOTIFICATION_STORE_H_INCL__

#include "Common.h"
#include "UINotificationClass.h"
#include "UINotificationQueue.h"

namespace ultraschall { namespace reaper {

class UINotificationStore
{
public:
    UINotificationStore();
    ~UINotificationStore();

    inline void RegisterSuccess(const UnicodeString& str);
    inline void RegisterWarning(const UnicodeString& str);
    inline void RegisterError(const UnicodeString& str);
    inline void RegisterFatalError(const UnicodeString& str);

private:
    static const UnicodeString NOTIFICATION_SECTION_NAME;

    void RegisterNotification(const UINotificationClass severity, const UnicodeString& str);
    void DispatchNotifications();
    void DisplayNotifications();

    UINotificationQueue messageQueue_;
    void*               projectReference_;
};

inline void UINotificationStore::RegisterSuccess(const UnicodeString& str)
{
    RegisterNotification(UINotificationClass::NOTIFICATION_SUCCESS, str);
}

inline void UINotificationStore::RegisterWarning(const UnicodeString& str)
{
    RegisterNotification(UINotificationClass::NOTIFICATION_WARNING, str);
}

inline void UINotificationStore::RegisterError(const UnicodeString& str)
{
    RegisterNotification(UINotificationClass::NOTIFICATION_ERROR, str);
}

inline void UINotificationStore::RegisterFatalError(const UnicodeString& str)
{
    RegisterNotification(UINotificationClass::NOTIFICATION_FATAL_ERROR, str);
}

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_UI_NOTIFICATION_STORE_H_INCL__
