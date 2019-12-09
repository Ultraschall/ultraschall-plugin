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

#include "UINotificationStore.h"
#include "SystemProperties.h"

namespace ultraschall { namespace reaper {

const UnicodeString UINotificationStore::NOTIFICATION_SECTION_NAME("ultraschall_messages");

UINotificationStore::UINotificationStore() : projectReference_(ReaperGateway::QueryCurrentProject()) {}

UINotificationStore::~UINotificationStore()
{
    DispatchNotifications();

    messageQueue_.Clear();
    projectReference_ = nullptr;
}

void UINotificationStore::RegisterNotification(const UINotificationClass severity, const UnicodeString& str)
{
    messageQueue_.Add(severity, str);
}

void UINotificationStore::DispatchNotifications()
{
    PRECONDITION(projectReference_ != nullptr);
    PRECONDITION(messageQueue_.ItemCount() > 0);

    ClearNotifications();

    const size_t messageCount = messageQueue_.ItemCount();
    SystemProperty<int>::Set(NOTIFICATION_SECTION_NAME, "message_count", (int)messageCount);

    const UINotificationArray& messages_ = messageQueue_.Items();
    for(size_t i = 0; i < messages_.size(); ++i)
    {
        UnicodeStringStream is;
        is << "message_" << i;
        const UnicodeString key = is.str();

        is.clear();
        switch(messages_[i].Severity())
        {
            case UINotificationClass::NOTIFICATION_SUCCESS:
                is << "+";
                break;
            case UINotificationClass::NOTIFICATION_WARNING:
                is << "!";
                break;
            case UINotificationClass::NOTIFICATION_FATAL_ERROR:
            case UINotificationClass::NOTIFICATION_ERROR:
                is << "-";
                break;
            default:
                is << "?";
                break;
        }

        is << ";" << messages_[i].Str() << std::endl;
        const UnicodeString value = is.str();

        SystemProperty<UnicodeString>::Set(NOTIFICATION_SECTION_NAME, key, value);
    }
}

void UINotificationStore::DisplayNotifications()
{
    // TODO: Call LUA action
}

void UINotificationStore::ClearNotifications()
{
    PRECONDITION(projectReference_ != nullptr);
    PRECONDITION(messageQueue_.ItemCount() > 0);

    SystemProperty<UnicodeString>::Clear(NOTIFICATION_SECTION_NAME);
}

}} // namespace ultraschall::reaper
