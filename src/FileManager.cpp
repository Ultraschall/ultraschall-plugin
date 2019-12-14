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

#include "Application.h"
#include "FileManager.h"
#include "StringUtilities.h"
#include "Platform.h"

namespace ultraschall { namespace reaper {

UnicodeChar FileManager::PathSeparator()
{
    return Platform::QueryPathSeparator();
}

UnicodeString FileManager::AppendPath(const UnicodeString& prefix, const UnicodeString& appendix)
{
    return prefix + Platform::QueryPathSeparator() + appendix;
}

UnicodeString FileManager::StripPath(const UnicodeString& path)
{
    PRECONDITION_RETURN(path.empty() == false, UnicodeString());

    UnicodeString shortName;

    if(path.empty() == false)
    {
        shortName = path;

        const UnicodeString::size_type offset = path.rfind(FileManager::PathSeparator());
        if(offset != UnicodeString::npos)
        {
            shortName = path.substr(offset + 1, path.size()); // skip separator
        }
    }

    return shortName;
}

UnicodeStringArray FileManager::SplitPath(const UnicodeString& path)
{
    return UnicodeStringTokenize(path, PathSeparator());
}

bool FileManager::FileExists(const UnicodeString& path)
{
    return Platform::QueryFileExists(path);
}

size_t FileManager::FileExists(const UnicodeStringArray& paths)
{
    PRECONDITION_RETURN(paths.empty() == false, -1);

    size_t offset = -1;

    for(size_t i = 0; (i < paths.size()) && (offset == -1); i++)
    {
        if(FileExists(paths[i]) == true)
        {
            offset = i;
        }
    }

    return offset;
}

UnicodeString FileManager::QueryFileDirectory(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, UnicodeString());

    UnicodeString directory = ".";

    size_t offset = filename.find_last_of(Platform::QueryPathSeparator());
    if(offset != std::string::npos)
    {
        directory = filename.substr(0, offset);
    }

    return directory;
}

size_t FileManager::QueryFileSize(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, -1);
    PRECONDITION_RETURN(FileExists(filename) == true, -1);

    size_t size = -1;

    std::ifstream file(U2H(filename), std::ios::in | std::ios::binary | std::ios::ate);
    if(file.is_open() == true)
    {
        size = file.tellg();
        file.close();
    }

    return size;
}

bool FileManager::IsDiskSpaceAvailable(const UnicodeString& filename, const size_t requiredBytes)
{
    PRECONDITION_RETURN(filename.empty() == false, false);
    PRECONDITION_RETURN(requiredBytes != -1, false);

    bool isAvailable = false;

    const size_t availableSpace = Platform::QueryAvailableDiskSpace(QueryFileDirectory(filename));
    if(availableSpace != -1)
    {
        isAvailable = (requiredBytes <= availableSpace);
    }

    return isAvailable;
}

BinaryStream* FileManager::ReadBinaryFile(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, nullptr);

    BinaryStream* pStream = nullptr;

    const size_t fileSize = QueryFileSize(filename);
    if(fileSize != -1)
    {
        std::ifstream file(U2H(filename), std::ios::in | std::ios::binary);
        if(file.is_open() == true)
        {
            uint8_t* buffer = new uint8_t[fileSize];
            if(buffer != nullptr)
            {
                file.read(reinterpret_cast<char*>(buffer), fileSize);
                if(file)
                {
                    pStream = new BinaryStream(fileSize);
                    if(pStream != nullptr)
                    {
                        const bool succeeded = pStream->Write(0, buffer, fileSize);
                        if(succeeded == false)
                        {
                            SafeRelease(pStream);
                        }
                    }
                }

                SafeDeleteArray(buffer);
            }

            file.close();
        }
    }

    return pStream;
}

UnicodeStringArray FileManager::ReadTextFile(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, UnicodeStringArray());
    PRECONDITION_RETURN(FileExists(filename) == true, UnicodeStringArray());

    UnicodeStringArray lines;

    std::ifstream is(U2H(filename).c_str());
    UnicodeString line;
    while(std::getline(is, line))
    {
        lines.push_back(line);
    }

    return lines;
}

bool FileManager::WriteTextFile(const UnicodeString& filename, const UnicodeString& str)
{
    PRECONDITION_RETURN(filename.empty() == false, false);
    PRECONDITION_RETURN(IsDiskSpaceAvailable(filename, str.size()) == true, false);
    PRECONDITION_RETURN(str.empty() == false, false);

    bool status = false;

    std::ofstream os(U2H(filename).c_str());
    if(os.is_open() == true)
    {
        os << str << std::endl;
        os.close();
        status = true;
    }

    return status;
}

}} // namespace ultraschall::reaper
