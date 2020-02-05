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

#ifdef _WIN32
#define CURL_STATICLIB
#endif // #ifdef _WIN32
#include <curl/curl.h>
#include <curl/easy.h>

#include "HttpClient.h"

namespace ultraschall { namespace reaper {

static size_t ReceiveDataHandler(void* pData, size_t dataSize, size_t itemSize, void* pStream)
{
    PRECONDITION_RETURN(pData != 0, 0);
    PRECONDITION_RETURN(itemSize > 0, 0);
    PRECONDITION_RETURN(pStream != 0, 0);

    std::string        data((const char*)pData, (size_t)dataSize * itemSize);
    std::stringstream& os = *((std::stringstream*)pStream);
    os << data << std::endl;
    return dataSize * itemSize;
}

BinaryStream* HttpClient::Download(const UnicodeString& url)
{
    PRECONDITION_RETURN(url.empty(), nullptr);

    BinaryStream* pStream = new BinaryStream(4096);
    if(pStream != nullptr)
    {
        void* curlHandle = curl_easy_init();
        if(curlHandle != nullptr)
        {
            const UnicodeString encodedUrl = EncodeUrl(url);
            curl_easy_setopt(curlHandle, CURLOPT_URL, encodedUrl.c_str());
            curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curlHandle, CURLOPT_NOSIGNAL, 1);
            curl_easy_setopt(curlHandle, CURLOPT_ACCEPT_ENCODING, "deflate");
            curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, ReceiveDataHandler);

            std::stringstream out;
            curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &out);
            const CURLcode curlResult = curl_easy_perform(curlHandle);
            if(CURLE_OK == curlResult)
            {
                const uint8_t* ptr = reinterpret_cast<const uint8_t*>(out.str().c_str());
                pStream->Write(0, ptr, out.str().length());
            }

            curl_easy_cleanup(curlHandle);
            curlHandle = nullptr;
        }
    }

    return pStream;
}

UnicodeString HttpClient::EncodeUrl(const UnicodeString& url)
{
    PRECONDITION_RETURN(url.empty() == false, UnicodeString());

    UnicodeString encodedUrl;

    void* curlHandle = curl_easy_init();
    if(curlHandle != nullptr)
    {
        char* urlBuffer = curl_easy_escape(curlHandle, url.c_str(), static_cast<int>(url.length()));
        if(urlBuffer != nullptr)
        {
            encodedUrl = urlBuffer;
            curl_free(urlBuffer);
            urlBuffer = nullptr;
        }

        curl_easy_cleanup(curlHandle);
        curlHandle = nullptr;
    }

    return encodedUrl;
}

UnicodeString HttpClient::DecodeUrl(const UnicodeString& url)
{
    PRECONDITION_RETURN(url.empty() == false, UnicodeString());

    UnicodeString decodedUrl;

    void* curlHandle = curl_easy_init();
    if(curlHandle != nullptr)
    {
        char* urlBuffer = curl_easy_unescape(curlHandle, url.c_str(), static_cast<int>(url.length()), nullptr);
        if(urlBuffer != nullptr)
        {
            decodedUrl = urlBuffer;
            curl_free(urlBuffer);
            urlBuffer = nullptr;
        }

        curl_easy_cleanup(curlHandle);
        curlHandle = nullptr;
    }

    return decodedUrl;
}

}} // namespace ultraschall::reaper
