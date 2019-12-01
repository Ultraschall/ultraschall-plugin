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

#include "UIMessageSupervisor.h"
#include "ProjectProperties.h"

namespace ultraschall { namespace reaper {

const UnicodeString UIMessageSupervisor::MESSAGES_SECTION_NAME("ultraschall_messages");

UIMessageSupervisor::UIMessageSupervisor() : projectReference_(ReaperGateway::QueryCurrentProject()) {}

UIMessageSupervisor::~UIMessageSupervisor()
{
    DispatchMessages();

    messageQueue_.Clear();
    projectReference_ = nullptr;
}

void UIMessageSupervisor::RegisterMessage(const UIMessageClass severity, const UnicodeString& str)
{
    messageQueue_.Add(severity, str);
}

void UIMessageSupervisor::DispatchMessages()
{
    PRECONDITION(projectReference_ != nullptr);
    PRECONDITION(messageQueue_.ItemCount() > 0);

    ClearMessages();

    const size_t messageCount = messageQueue_.ItemCount();
    ProjectProperty<int>::Set(projectReference_, MESSAGES_SECTION_NAME, "message_count", (int)messageCount);

    const UIMessageArray& messages_ = messageQueue_.Items();
    for(size_t i = 0; i < messages_.size(); ++i)
    {
        UnicodeStringStream is;
        is << "message_" << i;
        const UnicodeString key = is.str();

        is.clear();
        switch(messages_[i].Severity())
        {
            case MESSAGE_SUCCESS:
                is << "+";
                break;
            case MESSAGE_WARNING:
                is << "!";
                break;
            case MESSAGE_FATAL_ERROR:
            case MESSAGE_ERROR:
                is << "-";
                break;
            default:
                is << "?";
                break;
        }

        is << ";" << messages_[i].Str();
        const UnicodeString value = is.str();

        ProjectProperty<UnicodeString>::Set(projectReference_, MESSAGES_SECTION_NAME, key, value);
    }
}

void UIMessageSupervisor::DisplayMessages() 
{
  //TODO: Call LUA action
}

void UIMessageSupervisor::ClearMessages()
{
    PRECONDITION(projectReference_ != nullptr);
    PRECONDITION(messageQueue_.ItemCount() > 0);

    ProjectProperty<UnicodeString>::Clear(projectReference_, MESSAGES_SECTION_NAME);
}

}} // namespace ultraschall::reaper
