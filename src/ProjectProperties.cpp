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

#include "ProjectProperties.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

template<>
void ProjectProperty<UnicodeString>::Set(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key,
    const UnicodeString& value)
{
    PRECONDITION(projectReference != nullptr);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);
    PRECONDITION(value.empty() == false);

    ReaperGateway::SetProjectValue(projectReference, section, key, value);
}

template<>
void ProjectProperty<bool>::Set(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key,
    const bool& value)
{
    PRECONDITION(projectReference != nullptr);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    const UnicodeString boolValue = value == true ? "true" :
                                                    "false";
    ReaperGateway::SetProjectValue(projectReference, section, key, boolValue);
}

template<>
void ProjectProperty<int>::Set(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key, const int& value)
{
    PRECONDITION(projectReference != nullptr);
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    UnicodeStringStream is;
    is << value;
    ReaperGateway::SetProjectValue(projectReference, section, key, is.str());
}

template<>
UnicodeString ProjectProperty<UnicodeString>::Query(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key)
{
    return RawValue(projectReference, section, key);
}

template<>
bool ProjectProperty<bool>::Query(
    ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key)
{
    bool value = false;

    const UnicodeString& rawValue = RawValue(projectReference, section, key);
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
int ProjectProperty<int>::Query(ProjectReference projectReference, const UnicodeString& section, const UnicodeString& key)
{
    int value = 0;

    const UnicodeString rawValue = RawValue(projectReference, section, key);
    if(rawValue.empty() == false)
    {
        value = UnicodeStringToInt(rawValue);
    }

    return value;
}

}} // namespace ultraschall::reaper
