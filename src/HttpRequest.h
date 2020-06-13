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

#ifndef __ULTRASCHALL_REAPER_HTTP_REQUEST_H_INCL__
#define __ULTRASCHALL_REAPER_HTTP_REQUEST_H_INCL__

#include "Common.h"
#include "SharedObject.h"

namespace ultraschall { namespace reaper {

enum class HttpRequestType
{
    GET
};

class HttpRequest : public SharedObject
{
public:
    static HttpRequest* Create(const HttpRequestType type, const UnicodeString& url);
    static HttpRequest* Create(
        const HttpRequestType type, const UnicodeString& url, const UnicodeStringDictionary& header);

    inline const UnicodeString&           Url() const;
    inline const UnicodeStringDictionary& Header() const;

protected:
    virtual ~HttpRequest();

    HttpRequest(const HttpRequestType type, const UnicodeString& url);
    HttpRequest(const HttpRequestType type, const UnicodeString& url, const UnicodeStringDictionary& header);

private:
    HttpRequestType         type_;
    UnicodeString           url_;
    UnicodeStringDictionary header_;
};

inline const UnicodeString& HttpRequest::Url() const
{
    return url_;
}

inline const UnicodeStringDictionary& HttpRequest::Header() const
{
    return header_;
}

}} // namespace ultraschall::reaper

#endif // #ifdef __ULTRASCHALL_REAPER_HTTP_REQUEST_H_INCL__
