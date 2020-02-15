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

#include "ID3V2.h"
#include "BinaryStream.h"
#include "FileManager.h"
#include "Picture.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

ID3V2Context* ID3V2StartTransaction(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);

    return new ID3V2Context(targetName);
}

bool ID3V2CommitTransaction(ID3V2Context*& pContext)
{
    PRECONDITION_RETURN(pContext != nullptr, false);
    PRECONDITION_RETURN(pContext->Tags() != nullptr, false);

    pContext->Target()->strip(taglib_mp3::File::ID3v1 | taglib_mp3::File::APE);
    const bool success = pContext->Target()->save(taglib_mp3::File::ID3v2, true, 3);
    SafeDelete(pContext);

    return success;
}

void ID3V2AbortTransaction(ID3V2Context*& context)
{
    SafeDelete(context);
}

void ID3V2RemoveAllFrames(ID3V2Context* pContext)
{
    PRECONDITION(pContext != nullptr);
    PRECONDITION(pContext->Tags() != nullptr);

    UnicodeStringArray FRAME_IDS
        = {"TALB", "TPE1", "TIT2", "TCON", "TYER", "TLEN", "COMM", "APIC", "CTOC", "CHAP"};
    std::for_each(FRAME_IDS.begin(), FRAME_IDS.end(), [&](const UnicodeString& FRAME_ID) {
        taglib::ByteVector frameId = taglib::ByteVector::fromCString(FRAME_ID.c_str());
        pContext->Tags()->removeFrames(frameId);
    });
}

bool InsertUTF16TextFrame(ID3V2Context* pContext, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(pContext != nullptr, false);
    PRECONDITION_RETURN(pContext->Tags() != nullptr, false);
    PRECONDITION_RETURN(id.size() == 4, false);

    bool success = false;

    if(text.empty() == false)
    {
        taglib_id3v2::TextIdentificationFrame* pTextFrame = new taglib_id3v2::TextIdentificationFrame(
            taglib::ByteVector::fromCString(id.c_str()), taglib::String::Type::UTF16);
        if(pTextFrame != 0)
        {
            pTextFrame->setTextEncoding(taglib::String::Type::UTF16);
            pTextFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            pContext->Tags()->addFrame(pTextFrame);
            success = true;
        }
    }
    else
    {
        success = true;
    }

    return success;
}

bool InsertUTF8TextFrame(ID3V2Context* pContext, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(pContext != nullptr, false);
    PRECONDITION_RETURN(pContext->Tags() != nullptr, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    if(text.empty() == false)
    {
        taglib_id3v2::TextIdentificationFrame* pTextFrame = new taglib_id3v2::TextIdentificationFrame(
            taglib::ByteVector::fromCString(id.c_str()), taglib::String::Type::UTF8);
        if(pTextFrame != nullptr)
        {
            pTextFrame->setTextEncoding(taglib::String::Type::Latin1);
            pTextFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            pContext->Tags()->addFrame(pTextFrame);
            success = true;
        }
    }
    else
    {
        success = true;
    }

    return success;
}

bool ID3V2InsertTextFrame(
    ID3V2Context* pContext, const UnicodeString& id, const UnicodeString& text, const CHAR_ENCODING encoding)
{
    if(UTF16 == encoding)
    {
        return InsertUTF16TextFrame(pContext, id, text);
    }
    else
    {
        return InsertUTF8TextFrame(pContext, id, text);
    }
}

bool ID3V2InsertCommentsFrame(ID3V2Context* pContext, const UnicodeString& text)
{
    PRECONDITION_RETURN(pContext != nullptr, false);
    PRECONDITION_RETURN(pContext->Tags() != nullptr, false);

    bool success = false;

    if(text.empty() == false)
    {
        taglib_id3v2::CommentsFrame* pCommentsFrame = new taglib_id3v2::CommentsFrame(taglib::String::Type::UTF16);
        if(pCommentsFrame != nullptr)
        {
            pCommentsFrame->setLanguage(taglib::ByteVector::fromCString("eng"));
            pCommentsFrame->setTextEncoding(taglib::String::Type::UTF16);
            pCommentsFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            pContext->Tags()->addFrame(pCommentsFrame);
            success = true;
        }
    }
    else
    {
        success = true;
    }

    return success;
}

bool ID3V2InsertChapterFrame(
    ID3V2Context* pContext, const UnicodeString& id, const UnicodeString& text, const uint32_t startTime,
    const uint32_t endTime)
{
    PRECONDITION_RETURN(pContext != nullptr, false);
    PRECONDITION_RETURN(pContext->Tags() != nullptr, false);
    PRECONDITION_RETURN(id.empty() == false, false);
    PRECONDITION_RETURN(text.empty() == false, false);
    PRECONDITION_RETURN(startTime != 0xffffffff, false);
    PRECONDITION_RETURN(endTime != 0xffffffff, false);

    bool success = false;

    const uint32_t              startOffset   = 0xffffffff;
    const uint32_t              endOffset     = 0xffffffff;
    taglib_id3v2::ChapterFrame* pChapterFrame = new taglib_id3v2::ChapterFrame(
        taglib::ByteVector::fromCString(id.c_str(), static_cast<unsigned int>(id.length())), startTime, endTime,
        startOffset, endOffset);
    if(pChapterFrame != nullptr)
    {
        taglib_id3v2::TextIdentificationFrame* pEmbeddedFrame = new taglib_id3v2::TextIdentificationFrame(
            taglib::ByteVector::fromCString("TIT2"), taglib::String::Type::UTF16);
        if(pEmbeddedFrame != nullptr)
        {
            pEmbeddedFrame->setTextEncoding(taglib::String::Type::UTF16);
            pEmbeddedFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            pChapterFrame->addEmbeddedFrame(pEmbeddedFrame);
            pContext->Tags()->addFrame(pChapterFrame);
            success = true;
        }
        else
        {
            SafeDelete(pChapterFrame);
            success = false;
        }
    }

    return success;
}

class AttachedPictureFrameV3 : public taglib_id3v2::AttachedPictureFrame
{
public:
    AttachedPictureFrameV3() : taglib_id3v2::AttachedPictureFrame()
    {
        header()->setVersion(3);
    }
};

taglib_id3v2::FrameList* CreateEmbeddedFrames(
    const UnicodeString& title, const UnicodeString& image, const UnicodeString& url)
{
    PRECONDITION_RETURN(title.empty() == false, nullptr);

    taglib_id3v2::FrameList* pFrameList = new taglib_id3v2::FrameList();
    if(pFrameList != nullptr)
    {
        pFrameList->setAutoDelete(true);

        if(title.empty() == false)
        {
            taglib_id3v2::TextIdentificationFrame* pTitleFrame = new taglib_id3v2::TextIdentificationFrame(
                taglib::ByteVector::fromCString("TIT2"), taglib::String::Type::UTF16);
            pTitleFrame->setTextEncoding(taglib::String::Type::UTF16);
            pTitleFrame->setText(taglib::String(title, taglib::String::Type::UTF8));

            pFrameList->append(pTitleFrame);
        }

        if(url.empty() == false)
        {
            taglib_id3v2::UserUrlLinkFrame* pUrlFrame
                = new taglib_id3v2::UserUrlLinkFrame(taglib::ByteVector::fromCString("WXXX"));
            pUrlFrame->setDescription(taglib::String("chapter url"));
            pUrlFrame->setUrl(url);

            pFrameList->append(pUrlFrame);
        }

        if(image.empty() == false)
        {
            BinaryStream* pPictureData = FileManager::ReadBinaryFile(image);
            if(pPictureData != nullptr)
            {
                uint8_t      imageHeader[10] = {0};
                const size_t imageHeaderSize = 10;
                if(pPictureData->Read(0, imageHeader, imageHeaderSize) == true)
                {
                    const UnicodeString mimeType = Picture::FormatString(imageHeader, imageHeaderSize);
                    if(mimeType.empty() == false)
                    {
                        taglib_id3v2::AttachedPictureFrame* pPictureFrame = new AttachedPictureFrameV3();
                        if(pPictureFrame != nullptr)
                        {
                            pPictureFrame->setTextEncoding(taglib::String::Type::Latin1);
                            pPictureFrame->setMimeType(mimeType);
                            pPictureFrame->setType(taglib_id3v2::AttachedPictureFrame::Type::Other);

                            const char*        pData    = reinterpret_cast<const char*>(pPictureData->Data());
                            unsigned int       dataSize = static_cast<unsigned int>(pPictureData->DataSize());
                            taglib::ByteVector pictureData;
                            pictureData.setData(pData, dataSize);
                            pPictureFrame->setPicture(pictureData);
                            pFrameList->append(pPictureFrame);
                        }
                    }
                }

                SafeRelease(pPictureData);
            }
        }
    }

    return pFrameList;
}

bool ID3V2InsertChapterFrame(
    ID3V2Context* pContext, const UnicodeString& id, const UnicodeString& text, const uint32_t startTime,
    const uint32_t endTime, const UnicodeString& image, const UnicodeString& url)
{
    PRECONDITION_RETURN(pContext != nullptr, false);
    PRECONDITION_RETURN(pContext->Tags() != nullptr, false);
    PRECONDITION_RETURN(id.empty() == false, false);
    PRECONDITION_RETURN(text.empty() == false, false);
    PRECONDITION_RETURN(startTime != 0xffffffff, false);
    PRECONDITION_RETURN(endTime != 0xffffffff, false);

    const uint32_t           startOffset = 0xffffffff;
    const uint32_t           endOffset   = 0xffffffff;
    taglib_id3v2::FrameList* pFrameList  = CreateEmbeddedFrames(text, image, url);
    if(pFrameList != nullptr)
    {
        taglib_id3v2::ChapterFrame* pChapterFrame = new taglib_id3v2::ChapterFrame(
            taglib::ByteVector::fromCString(id.c_str(), static_cast<unsigned int>(id.length())), startTime, endTime,
            startOffset, endOffset, *pFrameList);
        if(pChapterFrame != nullptr)
        {
            pContext->Tags()->addFrame(pChapterFrame);
        }
    }

    return true;
}

bool ID3V2InsertTableOfContentsFrame(ID3V2Context* pContext, const UnicodeStringArray& tableOfContentsItems)
{
    PRECONDITION_RETURN(pContext != nullptr, false);
    PRECONDITION_RETURN(pContext->Tags() != nullptr, false);
    PRECONDITION_RETURN(tableOfContentsItems.empty() == false, false);

    bool success = false;

    taglib::ByteVector                  tableOfContentsId = taglib::ByteVector::fromCString("toc");
    taglib_id3v2::TableOfContentsFrame* pTableOfContentsFrame
        = new taglib_id3v2::TableOfContentsFrame(tableOfContentsId);
    if(pTableOfContentsFrame != nullptr)
    {
        pTableOfContentsFrame->setIsTopLevel(true);
        pTableOfContentsFrame->setIsOrdered(true);
        for(size_t j = 0; j < tableOfContentsItems.size(); j++)
        {
            pTableOfContentsFrame->addChildElement(taglib::ByteVector::fromCString(tableOfContentsItems[j].c_str()));
        }

        pContext->Tags()->addFrame(pTableOfContentsFrame);
        success = true;
    }

    return success;
}

bool ID3V2InsertCoverPictureFrame(ID3V2Context* pContext, const UnicodeString& image)
{
    PRECONDITION_RETURN(pContext != nullptr, false);
    PRECONDITION_RETURN(pContext->Tags() != nullptr, false);
    PRECONDITION_RETURN(image.empty() == false, false);

    bool success = false;

    taglib_id3v2::AttachedPictureFrame* pPictureFrame = new AttachedPictureFrameV3();
    if(pPictureFrame != nullptr)
    {
        BinaryStream* pPictureData = FileManager::ReadBinaryFile(image);
        if(pPictureData != nullptr)
        {
            uint8_t      imageHeader[10] = {0};
            const size_t imageHeaderSize = 10;
            if(pPictureData->Read(0, imageHeader, imageHeaderSize) == true)
            {
                const UnicodeString mimeType = Picture::FormatString(imageHeader, imageHeaderSize);
                if(mimeType.empty() == false)
                {
                    pPictureFrame->setMimeType(mimeType);
                    const char*        pData    = reinterpret_cast<const char*>(pPictureData->Data());
                    unsigned int       dataSize = static_cast<unsigned int>(pPictureData->DataSize());
                    taglib::ByteVector coverData(pData, dataSize);
                    pPictureFrame->setPicture(coverData);

                    pContext->Tags()->addFrame(pPictureFrame);
                    success = true;
                }
            }

            SafeRelease(pPictureData);
        }
    }

    return success;
}

}} // namespace ultraschall::reaper
