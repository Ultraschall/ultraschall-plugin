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
#include "HttpRequest.h"
#include "HttpResponse.h"

namespace ultraschall { namespace reaper {

HttpClient::HttpClient() : handle_(curl_easy_init()) {}

HttpClient::~HttpClient()
{
    if(handle_ != nullptr)
    {
        curl_easy_cleanup(handle_);
        handle_ = nullptr;
    }
}

UnicodeString HttpClient::DownloadUrl(const UnicodeString& url)
{
    PRECONDITION_RETURN(handle_ != nullptr, UnicodeString());
    PRECONDITION_RETURN(url.empty(), UnicodeString());

    UnicodeString result;

    const UnicodeString encodedUrl = EncodeUrl(url);
    if(encodedUrl.empty() == false)
    {
        HttpRequest* pRequest = HttpRequest::Create(HttpRequestType::GET, encodedUrl);
        if(pRequest != nullptr)
        {
            curl_easy_setopt(handle_, CURLOPT_URL, pRequest->Url());
            curl_easy_setopt(handle_, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(handle_, CURLOPT_NOSIGNAL, 1);
            curl_easy_setopt(handle_, CURLOPT_ACCEPT_ENCODING, "deflate");
            curl_easy_setopt(handle_, CURLOPT_WRITEFUNCTION, ReceiveDataHandler);

            SequentialStream* pStream = new SequentialStream();
            if(pStream != nullptr)
            {
                curl_easy_setopt(handle_, CURLOPT_WRITEDATA, pStream);
                const CURLcode curlResult = curl_easy_perform(handle_);
                if(CURLE_OK == curlResult)
                {
                    HttpResponse* pResponse = HttpResponse::Create(HttpResultCode::SUCCESS, pStream);
                    if(pResponse != nullptr)
                    {
                        result = StreamToString(pResponse->Result());
                        SafeRelease(pResponse);
                    }
                }

                SafeRelease(pStream);
            }

            SafeRelease(pRequest);
        }
    }

    return result;
}

size_t HttpClient::ReceiveDataHandler(void* pData, size_t dataSize, size_t itemSize, void* pParam)
{
    PRECONDITION_RETURN(pData != 0, 0);
    PRECONDITION_RETURN(itemSize > 0, 0);
    PRECONDITION_RETURN(pParam != 0, 0);

    size_t result = -1;

    SequentialStream* pStream = reinterpret_cast<SequentialStream*>(pParam);
    if(pStream != nullptr)
    {
        if(pStream->Write(reinterpret_cast<uint8_t*>(pData), dataSize * itemSize) == true)
        {
            result = dataSize * itemSize;
        }
        
    }

    return result;
}

UnicodeString HttpClient::StreamToString(const SequentialStream* pStream)
{
    PRECONDITION_RETURN(pStream != nullptr, UnicodeString());
    PRECONDITION_RETURN(pStream->Data() != nullptr, UnicodeString());
    PRECONDITION_RETURN(pStream->DataSize() > 0, UnicodeString());

    UnicodeString result;

    const size_t stringSize = pStream->DataSize() + sizeof(UnicodeChar);
    UnicodeChar* pString    = new UnicodeChar[stringSize];
    if(pString != nullptr)
    {
        memset(pString, 0, stringSize);
        memcpy(pString, pStream->Data(), pStream->DataSize());
        result = pString;

        SafeDeleteArray(pString);
    }

    return result;
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
