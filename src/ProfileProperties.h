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

#ifndef __ULTRASCHALL_REAPER_PROFILE_PROPERTIES_H_INCL__
#define __ULTRASCHALL_REAPER_PROFILE_PROPERTIES_H_INCL__

#include "Common.h"
#include "ReaperGateway.h"

namespace ultraschall { namespace reaper {

template<class T> class ProfileProperty
{
public:
    typedef T value_type;

    static bool Exists(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
    {
        PRECONDITION_RETURN(profile.empty() == false, false);
        PRECONDITION_RETURN(section.empty() == false, false);
        PRECONDITION_RETURN(key.empty() == false, false);

        return ReaperGateway::HasProfileValue(profile, section, key);
    }

    static void Save(
        const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const value_type& value);

    static void Set(
        const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key, const value_type& value);

    static value_type Query(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key);

    static void Clear(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
    {
        PRECONDITION(profile.empty() == false);
        PRECONDITION(section.empty() == false);
        PRECONDITION(key.empty() == false);

        ReaperGateway::ClearProfileValue(profile, section, key);
    }

    static void Delete(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
    {
        PRECONDITION(profile.empty() == false);
        PRECONDITION(section.empty() == false);
        PRECONDITION(key.empty() == false);

        ReaperGateway::DeleteProfileValue(profile, section, key);
    }

private:
    static UnicodeString RawValue(const UnicodeString& profile, const UnicodeString& section, const UnicodeString& key)
    {
        PRECONDITION_RETURN(profile.empty() == false, UnicodeString());
        PRECONDITION_RETURN(section.empty() == false, UnicodeString());
        PRECONDITION_RETURN(key.empty() == false, UnicodeString());

        return ReaperGateway::ProfileValue(profile, section, key);
    }
};

static UnicodeString UPDATE_SECTION_NAME = "ultraschall_update";

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_PROFILE_PROPERTIES_H_INCL__
