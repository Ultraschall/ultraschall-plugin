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

#include "SystemProperties.h"
#include "StringUtilities.h"
#include "NotificationStore.h"

namespace ultraschall { namespace reaper {

template<>
void SystemProperty<UnicodeString>::Save(
    const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    ReaperGateway::SaveSystemValue(section, key, value);
}

template<> void SystemProperty<bool>::Save(const UnicodeString& section, const UnicodeString& key, const bool& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    const UnicodeString boolValue = (value == true) ? "true" : "false";
    ReaperGateway::SaveSystemValue(section, key, boolValue);
}

template<> void SystemProperty<int>::Save(const UnicodeString& section, const UnicodeString& key, const int& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    UnicodeStringStream is;
    is << value;
    ReaperGateway::SaveSystemValue(section, key, is.str());
}

template<>
void SystemProperty<UnicodeString>::Set(
    const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    ReaperGateway::SetSystemValue(section, key, value);
}

template<> void SystemProperty<bool>::Set(const UnicodeString& section, const UnicodeString& key, const bool& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    const UnicodeString boolValue = (value == true) ? "true" : "false";
    ReaperGateway::SetSystemValue(section, key, boolValue);
}

template<> void SystemProperty<int>::Set(const UnicodeString& section, const UnicodeString& key, const int& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    UnicodeStringStream is;
    is << value;
    ReaperGateway::SetSystemValue(section, key, is.str());
}

template<> UnicodeString SystemProperty<UnicodeString>::Query(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(section.empty() == false, UnicodeString());
    PRECONDITION_RETURN(key.empty() == false, UnicodeString());

    return RawValue(section, key);
}

template<> bool SystemProperty<bool>::Query(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(section.empty() == false, false);
    PRECONDITION_RETURN(key.empty() == false, false);

    bool value = false;

    const UnicodeString& rawValue = RawValue(section, key);
    if(rawValue.empty() == false)
    {
        if((StringLowercase(rawValue) == "true") || (UnicodeStringToInt(rawValue) != 0))
        {
            value = true;
        }
    }

    return value;
}

template<> int SystemProperty<int>::Query(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(section.empty() == false, -1);
    PRECONDITION_RETURN(key.empty() == false, -1);

    int value = -1;

    const UnicodeString rawValue = RawValue(section, key);
    if(rawValue.empty() == false)
    {
        value = UnicodeStringToInt(rawValue);
    }

    return value;
}

}} // namespace ultraschall::reaper
