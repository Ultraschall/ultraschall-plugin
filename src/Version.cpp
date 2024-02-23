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

#include "Version.h"

namespace ultraschall { namespace reaper {

Version::Version(const std::string& version)
{
   std::vector<std::string> tokens = SplitString(version, '.');
   if (tokens.size() > 0) {
      major_ = PositiveIntegerOrNull(tokens[0]);
   }
   if (tokens.size() > 1) {
      minor_ = PositiveIntegerOrNull(tokens[1]);
   }
   if (tokens.size() > 2) {
      patch_ = PositiveIntegerOrNull(tokens[2]);
   }
}

std::vector<std::string> Version::SplitString(const std::string& str, const char delimiter /*= ' '*/)
{
   std::vector<std::string> tokens;
   if (str.empty() == false) {
      std::stringstream ss(str);
      std::string token;
      while (std::getline(ss, token, delimiter)) {
         tokens.push_back(token);
      }
   }
   return tokens;
}

int32_t Version::PositiveIntegerOrNull(const std::string& str)
{
   int32_t result = 0;
   if (str.empty() == false) {
      try {
         result = std::stoi(str);
      }
      catch (const std::invalid_argument& e) {
         result = 0;
      }
      catch (const std::out_of_range& e) {
         result = 0;
      }
      if (result < 0) {
         result = 0;
      }
   }
   else {
      result = 0;
   }
   return result;
}

bool operator==(const Version& lhs, const Version& rhs)
{
   return lhs.major_ == rhs.major_ && lhs.minor_ == rhs.minor_ && lhs.patch_ == rhs.patch_;
}

bool operator!=(const Version& lhs, const Version& rhs)
{
   return (lhs == rhs) == false;
}

bool operator<(const Version& lhs, const Version& rhs)
{
   if (lhs.major_ < rhs.major_) {
      return true;
   }
   if (lhs.major_ > rhs.major_) {
      return false;
   }
   if (lhs.minor_ < rhs.minor_) {
      return true;
   }
   if (lhs.minor_ > rhs.minor_) {
      return false;
   }
   return lhs.patch_ < rhs.patch_;
}

bool operator<=(const Version& lhs, const Version& rhs)
{
   return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Version& lhs, const Version& rhs)
{
   return (lhs <= rhs) == false;
}

bool operator>=(const Version& lhs, const Version& rhs)
{
   return (lhs < rhs) == false;
}

}} // namespace ultraschall::reaper
