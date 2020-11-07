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

#include "ProfileSection.h"

namespace ultraschall { namespace reaper {

ProfileSection::ProfileSection(const UnicodeString& name) : name_(name) {}

UnicodeString ProfileSection::Value(const UnicodeString& key) const
{
    PRECONDITION_RETURN(key.empty() == false, UnicodeString());

    return UnicodeString();
}

bool ProfileSection::SetValue(const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION_RETURN(key.empty() == false, false);
    PRECONDITION_RETURN(value.empty() == false, false);

    return false;
}

void ProfileSection::DeleteValue(const UnicodeString& key)
{
    PRECONDITION(key.empty() == false);
}

}} // namespace ultraschall::reaper
