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

#include "NotificationStore.h"
#include "SystemProperties.h"

namespace ultraschall { namespace reaper {

const UnicodeString NotificationStore::NOTIFICATION_SECTION_NAME("ultraschall_messages");
const UnicodeString NotificationStore::NOTIFICATION_VALUE_COUNT_NAME("message_count");
const UnicodeString NotificationStore::NOTIFICATION_KEY_PREFIX_NAME("message_");

NotificationStore::NotificationStore(const UnicodeString& messageContext) : messageContext_(messageContext) {}

NotificationStore::~NotificationStore()
{
    DispatchNotifications();

    messageQueue_.Clear();
}

void NotificationStore::RegisterNotification(const NotificationClass severity, const UnicodeString& str)
{
    messageQueue_.Add(severity, str);
}

void NotificationStore::DispatchNotifications()
{
    PRECONDITION(messageQueue_.ItemCount() > 0);

    size_t messageCountSeed = SystemProperty<int>::Query(NOTIFICATION_SECTION_NAME, NOTIFICATION_VALUE_COUNT_NAME);
    if(-1 == messageCountSeed)
    {
        messageCountSeed = 0;
    }

    const size_t messageCount = messageCountSeed + messageQueue_.ItemCount();
    SystemProperty<int>::Set(NOTIFICATION_SECTION_NAME, "message_count", static_cast<int>(messageCount));

    const NotificationArray& messages_ = messageQueue_.Items();
    for(size_t i = 0; i < messages_.size(); ++i)
    {
        UnicodeStringStream keyStream;
        keyStream << NOTIFICATION_KEY_PREFIX_NAME << (static_cast<int>(messageCountSeed) + i);
        const UnicodeString key = keyStream.str();

        UnicodeStringStream valueStream;
        switch(messages_[i].Severity())
        {
            case NotificationClass::NOTIFICATION_SUCCESS:
                valueStream << "+";
                break;
            case NotificationClass::NOTIFICATION_WARNING:
                valueStream << "!";
                break;
            case NotificationClass::NOTIFICATION_FATAL_ERROR:
            case NotificationClass::NOTIFICATION_ERROR:
                valueStream << "-";
                break;
            default:
                valueStream << "?";
                break;
        }

        valueStream << ";" << ((messageContext_.empty() == false) ? messageContext_ : "<Unknown>");
        valueStream << ";" << messages_[i].Str() << std::endl;
        const UnicodeString value = valueStream.str();
        SystemProperty<UnicodeString>::Set(NOTIFICATION_SECTION_NAME, key, value);
    }
}

void NotificationStore::ClearNotifications()
{
    size_t messageCount = SystemProperty<int>::Query(NOTIFICATION_SECTION_NAME, NOTIFICATION_VALUE_COUNT_NAME);
    if(-1 == messageCount)
    {
        messageCount = 0;
    }

    for(size_t i = 0; i < messageCount; i++)
    {
        UnicodeStringStream keyStream;
        keyStream << NOTIFICATION_KEY_PREFIX_NAME << (static_cast<int>(messageCount) + i);
        const UnicodeString key = keyStream.str();
        SystemProperty<int>::Clear(NOTIFICATION_SECTION_NAME, key);
    }
}

void NotificationStore::DisplayNotifications()
{
    // TODO: Call LUA action
    ClearNotifications();
}

}} // namespace ultraschall::reaper
