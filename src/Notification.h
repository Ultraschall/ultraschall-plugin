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

#ifndef __ULTRASCHALL_REAPER_NOTIFICATION_H_INCL__
#define __ULTRASCHALL_REAPER_NOTIFICATION_H_INCL__

#include "Common.h"
#include "NotificationClass.h"

namespace ultraschall { namespace reaper {

class Notification
{
public:
    Notification(const NotificationClass severity, const UnicodeString& str);

    inline NotificationClass    Severity() const;
    inline const UnicodeString& Str() const;

    inline bool IsValid() const;

private:
    const NotificationClass severity_ = NotificationClass::INVALID_NOTIFICATION_CLASS;
    const UnicodeString     str_;
};

inline NotificationClass Notification::Severity() const
{
    return severity_;
}

inline const UnicodeString& Notification::Str() const
{
    return str_;
}

inline bool Notification::IsValid() const
{
    return (Str().empty() == false) && (Severity() != NotificationClass::INVALID_NOTIFICATION_CLASS);
}

typedef std::vector<Notification> NotificationArray;

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_NOTIFICATION_H_INCL__
