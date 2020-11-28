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

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <shlobj.h>

#include "PlatformGateway.h"
#include "ReaperGateway.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

UnicodeString PlatformGateway::QueryReaperProfilePath()
{
    UnicodeString directory;

    WideUnicodeChar* unicodeString = nullptr;
    const HRESULT    hr            = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, (PWSTR*)&unicodeString);
    if(SUCCEEDED(hr))
    {
        directory = WU2U(unicodeString);
        CoTaskMemFree(unicodeString);
        unicodeString = nullptr;
    }

    return directory;
}

UnicodeChar PlatformGateway::QueryPathSeparator()
{
    return '\\';
}

size_t PlatformGateway::QueryAvailableDiskSpace(const UnicodeString& directory)
{
    PRECONDITION_RETURN(directory.empty() == false, -1);

    size_t         availableSpace           = -1;
    ULARGE_INTEGER freeBytesAvailableToUser = {0};
    if(GetDiskFreeSpaceEx(U2H(directory).c_str(), &freeBytesAvailableToUser, nullptr, nullptr) != FALSE)
    {
        availableSpace = freeBytesAvailableToUser.QuadPart;
    }

    return availableSpace;
}

UnicodeString PlatformGateway::SelectChaptersFile(
    const UnicodeString& dialogCaption, const UnicodeString&, const UnicodeString&)
{
    static const UnicodeString fileExtensions = "MP4 chapters|*.chapters.txt|All files|*.*";
    WideUnicodeString          result;

    UnicodeStringArray     filterSpecs = UnicodeStringTokenize(fileExtensions, UnicodeChar('|'));
    WideUnicodeStringArray wideFileExtensions;
    for(size_t i = 0; i < filterSpecs.size(); i++)
    {
        wideFileExtensions.push_back(UnicodeStringToWideUnicodeString(filterSpecs[i]));
    }

    const size_t       filterCount = filterSpecs.size() / 2;
    COMDLG_FILTERSPEC* filters     = SafeAllocArray<COMDLG_FILTERSPEC>(filterCount);
    if(filters != nullptr)
    {
        for(size_t j = 0; j < filterCount; ++j)
        {
            const size_t offset = j * 2;
            filters[j].pszName  = (LPCWSTR)wideFileExtensions[offset].c_str();
            filters[j].pszSpec  = (LPCWSTR)wideFileExtensions[offset + 1].c_str();
        }

        IFileOpenDialog* pfod = nullptr;
        HRESULT          hr   = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&pfod));
        if(SUCCEEDED(hr))
        {
            pfod->SetTitle(reinterpret_cast<LPCWSTR>(U2WU(dialogCaption).c_str()));
            pfod->SetFileTypes(static_cast<UINT>(filterCount), filters);

            FILEOPENDIALOGOPTIONS fos = FOS_STRICTFILETYPES | FOS_FILEMUSTEXIST;
            pfod->SetOptions(fos);

            hr = pfod->Show(reinterpret_cast<HWND>(ReaperGateway::View()));
            if(SUCCEEDED(hr))
            {
                IShellItem* psi = nullptr;
                hr              = pfod->GetResult(&psi);
                if(SUCCEEDED(hr))
                {
                    LPWSTR fileSystemPath = nullptr;
                    hr                    = psi->GetDisplayName(SIGDN_FILESYSPATH, &fileSystemPath);
                    if(SUCCEEDED(hr) && (nullptr != fileSystemPath))
                    {
                        result = reinterpret_cast<WideUnicodeChar*>(fileSystemPath);
                        CoTaskMemFree(fileSystemPath);
                    }

                    SafeRelease(psi);
                }
            }

            SafeRelease(pfod);
        }

        SafeDeleteArray(filters);
    }

    return WU2U(result);
}

UnicodeString PlatformGateway::SelectAudioFile(
    const UnicodeString& dialogCaption, const UnicodeString&, const UnicodeString&)
{
    static const UnicodeString fileExtensions = "MP3 file|*.mp3|All files|*.*";
    WideUnicodeString          result;

    UnicodeStringArray     filterSpecs = UnicodeStringTokenize(fileExtensions, UnicodeChar('|'));
    WideUnicodeStringArray wideFileExtensions;
    for(size_t i = 0; i < filterSpecs.size(); i++)
    {
        wideFileExtensions.push_back(UnicodeStringToWideUnicodeString(filterSpecs[i]));
    }

    const size_t       filterCount = filterSpecs.size() / 2;
    COMDLG_FILTERSPEC* filters     = SafeAllocArray<COMDLG_FILTERSPEC>(filterCount);
    if(filters != nullptr)
    {
        for(size_t j = 0; j < filterCount; ++j)
        {
            const size_t offset = j * 2;
            filters[j].pszName  = (LPCWSTR)wideFileExtensions[offset].c_str();
            filters[j].pszSpec  = (LPCWSTR)wideFileExtensions[offset + 1].c_str();
        }

        IFileOpenDialog* pfod = nullptr;
        HRESULT          hr   = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&pfod));
        if(SUCCEEDED(hr))
        {
            pfod->SetTitle(reinterpret_cast<LPCWSTR>(U2WU(dialogCaption).c_str()));
            pfod->SetFileTypes(static_cast<UINT>(filterCount), filters);

            FILEOPENDIALOGOPTIONS fos = FOS_STRICTFILETYPES | FOS_FILEMUSTEXIST;
            pfod->SetOptions(fos);

            hr = pfod->Show(reinterpret_cast<HWND>(ReaperGateway::View()));
            if(SUCCEEDED(hr))
            {
                IShellItem* psi = nullptr;
                hr              = pfod->GetResult(&psi);
                if(SUCCEEDED(hr))
                {
                    LPWSTR fileSystemPath = nullptr;
                    hr                    = psi->GetDisplayName(SIGDN_FILESYSPATH, &fileSystemPath);
                    if(SUCCEEDED(hr) && (nullptr != fileSystemPath))
                    {
                        result = reinterpret_cast<WideUnicodeChar*>(fileSystemPath);
                        CoTaskMemFree(fileSystemPath);
                    }

                    SafeRelease(psi);
                }
            }

            SafeRelease(pfod);
        }

        SafeDeleteArray(filters);
    }

    return WU2U(result);
}

UnicodeString PlatformGateway::SelectPictureFile(
    const UnicodeString& dialogCaption, const UnicodeString&, const UnicodeString&)
{
    static const UnicodeString fileExtensions = "JPG file|*.jpg|PNG file|*.png|All files|*.*";
    WideUnicodeString          result;

    UnicodeStringArray     filterSpecs = UnicodeStringTokenize(fileExtensions, UnicodeChar('|'));
    WideUnicodeStringArray wideFileExtensions;
    for(size_t i = 0; i < filterSpecs.size(); i++)
    {
        wideFileExtensions.push_back(UnicodeStringToWideUnicodeString(filterSpecs[i]));
    }

    const size_t       filterCount = filterSpecs.size() / 2;
    COMDLG_FILTERSPEC* filters     = SafeAllocArray<COMDLG_FILTERSPEC>(filterCount);
    if(filters != nullptr)
    {
        for(size_t j = 0; j < filterCount; ++j)
        {
            const size_t offset = j * 2;
            filters[j].pszName  = (LPCWSTR)wideFileExtensions[offset].c_str();
            filters[j].pszSpec  = (LPCWSTR)wideFileExtensions[offset + 1].c_str();
        }

        IFileOpenDialog* pfod = nullptr;
        HRESULT          hr   = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&pfod));
        if(SUCCEEDED(hr))
        {
            pfod->SetTitle(reinterpret_cast<LPCWSTR>(U2WU(dialogCaption).c_str()));
            pfod->SetFileTypes(static_cast<UINT>(filterCount), filters);

            FILEOPENDIALOGOPTIONS fos = FOS_STRICTFILETYPES | FOS_FILEMUSTEXIST;
            pfod->SetOptions(fos);

            hr = pfod->Show(reinterpret_cast<HWND>(ReaperGateway::View()));
            if(SUCCEEDED(hr))
            {
                IShellItem* psi = nullptr;
                hr              = pfod->GetResult(&psi);
                if(SUCCEEDED(hr))
                {
                    LPWSTR fileSystemPath = nullptr;
                    hr                    = psi->GetDisplayName(SIGDN_FILESYSPATH, &fileSystemPath);
                    if(SUCCEEDED(hr) && (nullptr != fileSystemPath))
                    {
                        result = reinterpret_cast<WideUnicodeChar*>(fileSystemPath);
                        CoTaskMemFree(fileSystemPath);
                    }

                    SafeRelease(psi);
                }
            }

            SafeRelease(pfod);
        }

        SafeDeleteArray(filters);
    }

    return WU2U(result);
}

UnicodeString PlatformGateway::SelectChaptersFileName(
    const UnicodeString& dialogCaption, const UnicodeString& initialDirectory, const UnicodeString& initialFile)
{
    static const UnicodeString fileExtensions = "MP4 chapters|*.chapters.txt|All files|*.*";
    WideUnicodeString          result;

    UnicodeStringArray     filterSpecs = UnicodeStringTokenize(fileExtensions, UnicodeChar('|'));
    WideUnicodeStringArray wideFileExtensions;
    for(size_t i = 0; i < filterSpecs.size(); i++)
    {
        wideFileExtensions.push_back(UnicodeStringToWideUnicodeString(filterSpecs[i]));
    }

    const size_t       filterCount = filterSpecs.size() / 2;
    COMDLG_FILTERSPEC* filters     = SafeAllocArray<COMDLG_FILTERSPEC>(filterCount);
    if(filters != nullptr)
    {
        for(size_t j = 0; j < filterCount; ++j)
        {
            const size_t offset = j * 2;
            filters[j].pszName  = (LPCWSTR)wideFileExtensions[offset].c_str();
            filters[j].pszSpec  = (LPCWSTR)wideFileExtensions[offset + 1].c_str();
        }

        IFileSaveDialog* pfsd = nullptr;
        HRESULT          hr   = CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&pfsd));
        if(SUCCEEDED(hr))
        {
            pfsd->SetDefaultExtension(L"chapters.txt");
            pfsd->SetTitle(reinterpret_cast<LPCWSTR>(U2WU(dialogCaption).c_str()));
            pfsd->SetFileTypes(static_cast<UINT>(filterCount), filters);

            if(initialDirectory.empty() == false)
            {
                IShellItem* psi = 0;
                hr              = SHCreateItemFromParsingName(
                    reinterpret_cast<LPCWSTR>(U2WU(initialDirectory).c_str()), nullptr, IID_PPV_ARGS(&psi));
                if(SUCCEEDED(hr))
                {
                    pfsd->SetFolder(psi);
                    SafeRelease(psi);
                }
            }

            if(initialFile.empty() == false)
            {
                pfsd->SetFileName(reinterpret_cast<LPCWSTR>(U2WU(initialFile).c_str()));
            }

            FILEOPENDIALOGOPTIONS fos = FOS_OVERWRITEPROMPT | FOS_CREATEPROMPT;
            pfsd->SetOptions(fos);

            hr = pfsd->Show(reinterpret_cast<HWND>(ReaperGateway::View()));
            if(SUCCEEDED(hr))
            {
                IShellItem* psi = nullptr;
                hr              = pfsd->GetResult(&psi);
                if(SUCCEEDED(hr))
                {
                    LPWSTR fileSystemPath = nullptr;
                    hr                    = psi->GetDisplayName(SIGDN_FILESYSPATH, &fileSystemPath);
                    if(SUCCEEDED(hr) && (nullptr != fileSystemPath))
                    {
                        result = reinterpret_cast<WideUnicodeChar*>(fileSystemPath);
                        CoTaskMemFree(fileSystemPath);
                    }

                    SafeRelease(psi);
                }
            }

            SafeRelease(pfsd);
        }

        SafeDeleteArray(filters);
    }

    return WU2U(result);
}

}} // namespace ultraschall::reaper
