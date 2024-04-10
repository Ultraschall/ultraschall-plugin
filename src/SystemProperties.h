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

#ifndef __ULTRASCHALL_REAPER_SYSTEM_PROPERTIES_H_INCL__
#define __ULTRASCHALL_REAPER_SYSTEM_PROPERTIES_H_INCL__

#include "Common.h"
#include "ReaperGateway.h"

namespace ultraschall { namespace reaper {

/// @brief The SystemProperty class implements a wrapper for system properties.
/// @tparam T The type of the system property.
template<class T> class SystemProperty
{
public:
   /// @brief The value type of the system property.
   typedef T value_type;

   /// @brief Checks whether a system property exists.
   /// @param section The section of the system property.
   /// @param key The key of the system property.
   /// @return <b>true</b> if the system property exists, <b>false</b> otherwise.
   static bool Exists(const UnicodeString& section, const UnicodeString& key)
   {
      PRECONDITION_RETURN(section.empty() == false, false);
      PRECONDITION_RETURN(key.empty() == false, false);

      return ReaperGateway::HasSystemValue(section, key);
   }

   /// @brief Saves a system property.
   /// @param section The section of the system property.
   /// @param key The key of the system property.
   /// @param value The value of the system property.
   static void Save(const UnicodeString& section, const UnicodeString& key, const value_type& value);

   /// @brief Sets a system property.
   /// @param section The section of the system property.
   /// @param key The key of the system property.
   /// @param value The value of the system property.
   static void Set(const UnicodeString& section, const UnicodeString& key, const value_type& value);

   /// @brief Queries a system property.
   /// @param section The section of the system property.
   /// @param key The key of the system property.
   /// @return The value of the system property.
   static value_type Query(const UnicodeString& section, const UnicodeString& key);

   /// @brief Clears a system property.
   /// @param section The section of the system property.
   /// @param key The key of the system property.
   static void Clear(const UnicodeString& section, const UnicodeString& key)
   {
      PRECONDITION(section.empty() == false);
      PRECONDITION(key.empty() == false);

      ReaperGateway::ClearSystemValue(section, key);
   }

   /// @brief Deletes a system property.
   /// @param section The section of the system property.
   /// @param key The key of the system property.
   static void Delete(const UnicodeString& section, const UnicodeString& key)
   {
      PRECONDITION(section.empty() == false);
      PRECONDITION(key.empty() == false);

      ReaperGateway::DeleteSystemValue(section, key);
   }

private:
   static UnicodeString RawValue(const UnicodeString& section, const UnicodeString& key)
   {
      PRECONDITION_RETURN(section.empty() == false, UnicodeString());
      PRECONDITION_RETURN(key.empty() == false, UnicodeString());

      return ReaperGateway::SystemValue(section, key);
   }
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_SYSTEM_PROPERTIES_H_INCL__
