//
////////////////////////////////////////////////////////////////////////////////
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

#ifndef __ULTRASCHALL_REAPER_NOTIFICATION_QUEUE_H_INCL__
#define __ULTRASCHALL_REAPER_NOTIFICATION_QUEUE_H_INCL__

#include "Common.h"
#include "Notification.h"

namespace ultraschall { namespace reaper {

/// @brief The NotificationQueue class implements a queue for notifications.
class NotificationQueue
{
public:
   /// @brief The NotificationQueue constructor.
   NotificationQueue();

   /// @brief The NotificationQueue destructor.
   ~NotificationQueue();

   /// @brief Adds a new notification to the queue.
   /// @param message The notification to be added.
   void Add(const Notification& message);

   /// @brief Adds a new notification to the queue.
   /// @param severity The severity of the notification.
   /// @param str The notification message.
   void Add(const NotificationClass severity, const UnicodeString& str);

   /// @brief Clears the queue.
   void Clear();

   /// @brief Returns the notifications in the queue.
   /// @return The notifications in the queue.
   const NotificationArray& Items() const;

   /// @brief Returns the number of notifications in the queue.
   /// @return The number of notifications in the queue.
   size_t ItemCount() const;

private:
   NotificationQueue(const NotificationQueue&)            = delete;
   NotificationQueue& operator=(const NotificationQueue&) = delete;

   NotificationArray items_;
   mutable std::recursive_mutex itemsLock_;
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_NOTIFICATION_QUEUE_H_INCL__
