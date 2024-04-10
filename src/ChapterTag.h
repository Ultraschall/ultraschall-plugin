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

#ifndef __ULTRASCHALL_REAPER_CHAPTER_TAG_H_INCL__
#define __ULTRASCHALL_REAPER_CHAPTER_TAG_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

/// @brief The ChapterTag class represents a single chapter tag.
class ChapterTag
{
public:
   /// @brief The default constructor initializes a new ChapterTag instance.
   ChapterTag() : position_(Globals::INVALID_MARKER_POSITION) {}

   /// @brief  The constructor initializes a new ChapterTag instance.
   ChapterTag(const double position, const UnicodeString& title) : position_(position), title_(title) {}

   /// @brief  The constructor initializes a new ChapterTag instance.
   ChapterTag(const double position, const UnicodeString& title, const UnicodeString& image, const UnicodeString& url) :
      position_(position), title_(title), image_(image), url_(url)
   {}

   /// @brief Returns the starting position of the chapter
   double Position() const
   {
      return position_;
   }

   /// @brief Returns the title of the chapter
   const UnicodeString& Title() const
   {
      return title_;
   }

   /// @brief Returns the file path of the chapter image
   const UnicodeString& Image() const
   {
      return image_;
   }

   /// @brief Sets the file path of the chapter image
   void SetImage(const UnicodeString& image)
   {
      image_ = image;
   }

   /// @brief Returns the URL of the chapter reference
   const UnicodeString& Url() const
   {
      return url_;
   }

   /// @brief Sets the URL of the chapter reference
   void SetUrl(const UnicodeString& url)
   {
      url_ = url;
   }

private:
   double position_;
   UnicodeString title_;
   UnicodeString image_;
   UnicodeString url_;
};

/// @brief The ChapterTagArray type represents an array of chapter tags.
typedef std::vector<ChapterTag> ChapterTagArray;

/// @brief The ChapterTagDictionary type represents a dictionary of chapter tags.
typedef std::map<double, ChapterTag> ChapterTagDictionary;

/// @brief The ChapterImageArray type represents an array of chapter images.
typedef std::vector<UnicodeString> ChapterImageArray;

/// @brief The ChapterImageDictionary type represents a dictionary of chapter images.
typedef std::map<double, UnicodeString> ChapterImageDictionary;

/// @brief The ChapterUrlArray type represents an array of chapter URLs.
typedef std::vector<UnicodeString> ChapterUrlArray;

/// @brief The ChapterUrlDictionary type represents a dictionary of chapter URLs.
typedef std::map<double, UnicodeString> ChapterUrlDictionary;

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_CHAPTER_TAG_H_INCL__
