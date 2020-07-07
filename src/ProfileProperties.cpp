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

#include "ProfileProperties.h"
#include "StringUtilities.h"
#include "NotificationStore.h"

namespace ultraschall { namespace reaper {

template<>
void ProfileProperty<UnicodeString>::Save(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION(profile.empty() == false);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    ReaperGateway::SaveProfileValue(profile, section, key, value);
}

template<>
void ProfileProperty<bool>::Save(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const bool& value)
{
    PRECONDITION(profile.empty() == false);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    const UnicodeString boolValue = (value == true) ? "true" : "false";
    ReaperGateway::SaveProfileValue(profile, section, key, boolValue);
}

template<>
void ProfileProperty<int>::Save(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const int& value)
{
    PRECONDITION(profile.empty() == false);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    UnicodeStringStream is;
    is << value;
    ReaperGateway::SaveProfileValue(profile, section, key, is.str());
}

template<>
void ProfileProperty<UnicodeString>::Set(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION(profile.empty() == false);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    ReaperGateway::SetProfileValue(profile, section, key, value);
}

template<>
void ProfileProperty<bool>::Set(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const bool& value)
{
    PRECONDITION(profile.empty() == false);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    const UnicodeString boolValue = (value == true) ? "true" : "false";
    ReaperGateway::SetProfileValue(profile, section, key, boolValue);
}

template<>
void ProfileProperty<int>::Set(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const int& value)
{
    PRECONDITION(profile.empty() == false);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    UnicodeStringStream is;
    is << value;
    ReaperGateway::SetProfileValue(profile, section, key, is.str());
}

template<>
UnicodeString ProfileProperty<UnicodeString>::Query(
    const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(profile.empty() == false, UnicodeString());
    PRECONDITION_RETURN(section.empty() == false, UnicodeString());
    PRECONDITION_RETURN(key.empty() == false, UnicodeString());

    return RawValue(profile, section, key);
}

template<>
bool ProfileProperty<bool>::Query(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(profile.empty() == false, false);
    PRECONDITION_RETURN(section.empty() == false, false);
    PRECONDITION_RETURN(key.empty() == false, false);

    bool value = false;

    const UnicodeString& rawValue = RawValue(profile, section, key);
    if(rawValue.empty() == false)
    {
        if((StringLowercase(rawValue) == "true") || (UnicodeStringToInt(rawValue) != 0))
        {
            value = true;
        }
    }

    return value;
}

template<>
int ProfileProperty<int>::Query(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(profile.empty() == false, -1);
    PRECONDITION_RETURN(section.empty() == false, -1);
    PRECONDITION_RETURN(key.empty() == false, -1);

    int value = -1;

    const UnicodeString rawValue = RawValue(profile, section, key);
    if(rawValue.empty() == false)
    {
        value = UnicodeStringToInt(rawValue);
    }

    return value;
}

}} // namespace ultraschall::reaper
