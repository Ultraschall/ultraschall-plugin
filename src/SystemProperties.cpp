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
#include "UINotificationStore.h"

namespace ultraschall { namespace reaper {

static const char* THEME_VERSION_KEY_NAME  = "theme";
static const char* PLUGIN_VERSION_KEY_NAME = "plugin";
static const char* VERSION_VALUE_NAME      = "20180114";

template<> UnicodeString SystemProperty<UnicodeString>::Query(const UnicodeString& section, const UnicodeString& key)
{
    return RawValue(section, key);
}

template<> bool SystemProperty<bool>::Query(const UnicodeString& section, const UnicodeString& key)
{
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
    int value = 0;

    const UnicodeString rawValue = RawValue(section, key);
    if(rawValue.empty() == false)
    {
        value = UnicodeStringToInt(rawValue);
    }

    return value;
}

}} // namespace ultraschall::reaper
