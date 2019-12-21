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

#include "ID3V2Writer.h"
#include "ID3V2Context.h"
#include "ID3V2.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

ID3V2Writer::~ID3V2Writer()
{
    SafeDelete(pContext_);
}

bool ID3V2Writer::Start(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(pContext_ == nullptr, false);

    bool contextStarted = false;

    pContext_ = ID3V2StartTransaction(targetName);
    if(pContext_ != nullptr)
    {
        ID3V2RemoveAllFrames(pContext_);
        contextStarted = true;
    }

    return contextStarted;
}

void ID3V2Writer::Stop(const bool commit)
{
    PRECONDITION(pContext_ != nullptr);

    if(true == commit)
    {
        ID3V2CommitTransaction(pContext_);
    }
    else
    {
        ID3V2AbortTransaction(pContext_);
    }
}

bool ID3V2Writer::InsertProperties(const UnicodeString& targetName, const MediaProperties& standardProperties)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(pContext_ != nullptr, false);

    bool success = true;

    const UnicodeString duration = UnicodeStringFromInt(pContext_->Duration());
    const UnicodeString encoder = "ultraschall4";

    static const size_t MAX_SIMPLE_FRAME_MAPPINGS  = 7;
    static const size_t MAX_COMPLEX_FRAME_MAPPINGS = 1;

    struct MAP_ULTRASCHALL_PROPERTIES_TO_REQUIRED_APPLE_TAGS
    {
        const UnicodeChar*   frameId;
        const CHAR_ENCODING  targetEncoding;
        const UnicodeString& text;
    }
    // clang-format off
    simpleFrameMappings[MAX_SIMPLE_FRAME_MAPPINGS] =
    {
      {"TALB", UTF16, standardProperties.Podcast()}, 
      {"TPE1", UTF16, standardProperties.Author()},
      {"TIT2", UTF16, standardProperties.Episode()}, 
      {"TCON", UTF16, standardProperties.Genre()},
      {"TYER", UTF8,  standardProperties.Date()},   
      {"TENC", UTF8,  encoder},   
      {"TLEN", UTF8,  duration}
    },
    complexFrameMapping[MAX_COMPLEX_FRAME_MAPPINGS] =
    {
      {"COMM", UTF16, standardProperties.Comments()}
    };
    // clang-format on

    for(size_t i = 0; (i < MAX_SIMPLE_FRAME_MAPPINGS) && (true == success); i++)
    {
        success = ID3V2InsertTextFrame(
            pContext_, simpleFrameMappings[i].frameId, simpleFrameMappings[i].text,
            simpleFrameMappings[i].targetEncoding);
    }

    if(true == success)
    {
        for(size_t i = 0; (i < MAX_COMPLEX_FRAME_MAPPINGS) && (true == success); i++)
        {
            success = ID3V2InsertCommentsFrame(pContext_, complexFrameMapping[i].text);
        }
    }

    return success;
}

bool ID3V2Writer::InsertCoverImage(const UnicodeString& targetName, const UnicodeString& coverImage)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(coverImage.empty() == false, false);
    PRECONDITION_RETURN(pContext_ != nullptr, false);

    return ID3V2InsertCoverPictureFrame(pContext_, coverImage);
}

bool ID3V2Writer::InsertChapterMarkers(const UnicodeString& targetName, const MarkerArray& chapterMarkers)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(chapterMarkers.empty() == false, false);
    PRECONDITION_RETURN(pContext_ != nullptr, false);
    PRECONDITION_RETURN(pContext_->Duration() > 0, false);

    bool success = false;

    UnicodeStringArray tableOfContentsItems;
    success = true;
    for(size_t i = 0; (i < chapterMarkers.size()) && (true == success); i++)
    {
        std::stringstream chapterId;
        chapterId << "chp" << i;
        UnicodeString tableOfContensItem = chapterId.str();
        tableOfContentsItems.push_back(tableOfContensItem);

        const uint32_t startTime = static_cast<uint32_t>(chapterMarkers[i].Position() * 1000);
        const uint32_t endTime   = (i < (chapterMarkers.size() - 1)) ?
                                     static_cast<uint32_t>(chapterMarkers[i + 1].Position() * 1000) :
                                     pContext_->Duration();
        success = ID3V2InsertChapterFrame(pContext_, tableOfContensItem, chapterMarkers[i].Name(), startTime, endTime);
    }

    if(true == success)
    {
        success = ID3V2InsertTableOfContentsFrame(pContext_, tableOfContentsItems);
    }

    return success;
}

}} // namespace ultraschall::reaper
