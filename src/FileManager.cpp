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

#include "FileManager.h"

#include "Application.h"
#include "PlatformGateway.h"
#include "StringUtilities.h"

#include <filesystem>

namespace ultraschall { namespace reaper {

UnicodeChar FileManager::PathSeparator()
{
    return PlatformGateway::QueryPathSeparator();
}

UnicodeString FileManager::AppendPath(const UnicodeString& prefix, const UnicodeString& appendix)
{
    return prefix + PlatformGateway::QueryPathSeparator() + appendix;
}

UnicodeString FileManager::StripPath(const UnicodeString& path)
{
    PRECONDITION_RETURN(path.empty() == false, UnicodeString());

    UnicodeString shortName;

    if (path.empty() == false) {
        shortName                             = path;

        const UnicodeString::size_type offset = path.rfind(FileManager::PathSeparator());
        if (offset != UnicodeString::npos) {
            shortName = path.substr(offset + 1, path.size()); // skip separator
        }
    }

    return shortName;
}

UnicodeStringArray FileManager::SplitPath(const UnicodeString& path)
{
    return UnicodeStringTokenize(path, PathSeparator());
}

bool FileManager::FileExists(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, false);

    bool fileExists = false;

    std::ifstream is(U2H(filename), std::ios::in | std::ios::binary);
    if (is.is_open() == true) {
        fileExists = true;
        is.close();
    }

    return fileExists;
}

size_t FileManager::FileExists(const UnicodeStringArray& paths)
{
    PRECONDITION_RETURN(paths.empty() == false, -1);

    size_t offset = -1;

    for (size_t i = 0; (i < paths.size()) && (offset == -1); i++) {
        if (FileExists(paths[i]) == true) {
            offset = i;
        }
    }

    return offset;
}

static std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}

static std::string str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
    return s;
}

UnicodeString FileManager::FindFile(const UnicodeString& path, const UnicodeString& name)
{
    PRECONDITION_RETURN(path.empty() == false, UnicodeString());
    PRECONDITION_RETURN(name.empty() == false, UnicodeString());

    std::string result;
    auto directoryEntries = std::filesystem::directory_iterator{std::filesystem::path(path)};
    for (auto& directoryEntry : directoryEntries) {
        if (directoryEntry.is_regular_file()) {
            const std::string lhs = str_tolower(directoryEntry.path().filename().string());
            const std::string rhs = str_tolower(name);
            if (lhs == rhs) {
                result = directoryEntry.path().filename().string();
            }
        }
    }
    return result;
}

UnicodeString FileManager::FindFile(const UnicodeString& path, const UnicodeStringArray& names)
{
    PRECONDITION_RETURN(path.empty() == false, UnicodeString());
    PRECONDITION_RETURN(names.empty() == false, UnicodeString());

    UnicodeString result;
    for (size_t i = 0; (i < names.size()) && (result.empty() == true); i++) {
        const std::string file = FindFile(path, names[i]);
        if (file.empty() == false) {
            result = names[i];
        }
    }
    return result;
}

UnicodeString FileManager::QueryFileDirectory(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, UnicodeString());

    UnicodeString directory = ".";

    size_t offset           = filename.find_last_of(PlatformGateway::QueryPathSeparator());
    if (offset != std::string::npos) {
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
    if (file.is_open() == true) {
        size = file.tellg();
        file.close();
    }

    return size;
}

UnicodeString FileManager::NormalizeFileName(const UnicodeString& targetName)
{
    UnicodeString firstStage  = targetName;
    UnicodeString secondStage = UnicodeStringCopyTrim(firstStage);
    return StringLowercase(secondStage);
}

FileManager::FILE_TYPE FileManager::QueryFileType(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, FILE_TYPE::UNKNOWN_FILE_TYPE);

    FILE_TYPE type                       = FILE_TYPE::UNKNOWN_FILE_TYPE;
    const UnicodeString cookedTargetName = NormalizeFileName(filename);
    const size_t extensionOffset         = cookedTargetName.rfind(".");
    if (extensionOffset != UnicodeString::npos) {
        const UnicodeString fileExtension = cookedTargetName.substr(extensionOffset + 1, cookedTargetName.length() - extensionOffset);
        if (fileExtension.empty() == false) {
            if ((fileExtension == "txt") || (fileExtension == "mp4chaps")) {
                type = FILE_TYPE::MP4CHAPS;
            }
            else if (fileExtension == "mp3") {
                type = FILE_TYPE::MP3;
            }
            else if ((fileExtension == "jpg") || (fileExtension == "jpeg")) {
                type = FILE_TYPE::JPEG;
            }
            else if (fileExtension == "png") {
                type = FILE_TYPE::PNG;
            }
            else {
                type = FILE_TYPE::UNKNOWN_FILE_TYPE;
            }
        }
    }

    return type;
}

bool FileManager::IsDiskSpaceAvailable(const UnicodeString& filename, const size_t requiredBytes)
{
    PRECONDITION_RETURN(filename.empty() == false, false);
    PRECONDITION_RETURN(requiredBytes != -1, false);

    bool isAvailable            = false;

    const size_t availableSpace = PlatformGateway::QueryAvailableDiskSpace(QueryFileDirectory(filename));
    if (availableSpace != -1) {
        isAvailable = (requiredBytes <= availableSpace);
    }

    return isAvailable;
}

BinaryStream* FileManager::ReadBinaryFile(const UnicodeString& filename)
{
    PRECONDITION_RETURN(filename.empty() == false, nullptr);

    BinaryStream* pStream = nullptr;

    const size_t fileSize = QueryFileSize(filename);
    if (fileSize != -1) {
        std::ifstream file(U2H(filename), std::ios::in | std::ios::binary);
        if (file.is_open() == true) {
            uint8_t* buffer = new uint8_t[fileSize];
            if (buffer != nullptr) {
                file.read(reinterpret_cast<char*>(buffer), fileSize);
                if (file) {
                    pStream = new BinaryStream(fileSize);
                    if (pStream != nullptr) {
                        const bool succeeded = pStream->Write(0, buffer, fileSize);
                        if (succeeded == false) {
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
    while (std::getline(is, line)) {
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
    if (os.is_open() == true) {
        os << str;
        os.close();
        status = true;
    }

    return status;
}
}} // namespace ultraschall::reaper
