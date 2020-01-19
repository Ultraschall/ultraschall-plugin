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

bool ID3V2CommitTransaction(ID3V2Context*& context)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);

    context->Target()->strip(taglib_mp3::File::ID3v1 | taglib_mp3::File::APE);
    const bool success = context->Target()->save(taglib_mp3::File::ID3v2, true, 3);
    SafeDelete(context);

    return success;
}

void ID3V2AbortTransaction(ID3V2Context*& context)
{
    SafeDelete(context);
}

void ID3V2RemoveAllFrames(ID3V2Context* context)
{
    PRECONDITION(context != 0);
    PRECONDITION(context->Tags() != 0);

    UnicodeStringArray FRAME_IDS
        = {"TALB", "TPE1", "TIT2", "TCON", "TYER", "TENC", "TLEN", "COMM", "APIC", "CTOC", "CHAP"};
    std::for_each(FRAME_IDS.begin(), FRAME_IDS.end(), [&](const UnicodeString& FRAME_ID) {
        taglib::ByteVector frameId = taglib::ByteVector::fromCString(FRAME_ID.c_str());
        context->Tags()->removeFrames(frameId);
    });
}

bool InsertUTF16TextFrame(ID3V2Context* context, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.size() == 4, false);

    bool success = false;

    if(text.empty() == false)
    {
        taglib_id3v2::TextIdentificationFrame* textFrame = new taglib_id3v2::TextIdentificationFrame(
            taglib::ByteVector::fromCString(id.c_str()), taglib::String::Type::UTF16);
        if(textFrame != 0)
        {
            textFrame->setTextEncoding(taglib::String::Type::UTF16);
            textFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            context->Tags()->addFrame(textFrame);
            success = true;
        }
    }
    else
    {
        success = true;
    }

    return success;
}

bool InsertUTF8TextFrame(ID3V2Context* context, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    if(text.empty() == false)
    {
        taglib_id3v2::TextIdentificationFrame* textFrame = new taglib_id3v2::TextIdentificationFrame(
            taglib::ByteVector::fromCString(id.c_str()), taglib::String::Type::UTF8);
        if(textFrame != 0)
        {
            textFrame->setTextEncoding(taglib::String::Type::Latin1);
            textFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            context->Tags()->addFrame(textFrame);
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
    ID3V2Context* context, const UnicodeString& id, const UnicodeString& text, const CHAR_ENCODING encoding)
{
    if(encoding == UTF16)
    {
        return InsertUTF16TextFrame(context, id, text);
    }
    else
    {
        return InsertUTF8TextFrame(context, id, text);
    }
}

bool ID3V2InsertCommentsFrame(ID3V2Context* context, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);

    bool success = false;

    if(text.empty() == false)
    {
        taglib_id3v2::CommentsFrame* commentsFrame = new taglib_id3v2::CommentsFrame(taglib::String::Type::UTF16);
        if(commentsFrame != 0)
        {
            commentsFrame->setLanguage(taglib::ByteVector::fromCString("eng"));
            commentsFrame->setTextEncoding(taglib::String::Type::UTF16);
            commentsFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            context->Tags()->addFrame(commentsFrame);
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
    ID3V2Context* context, const UnicodeString& id, const UnicodeString& text, const uint32_t startTime,
    const uint32_t endTime)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);
    PRECONDITION_RETURN(text.empty() == false, false);
    PRECONDITION_RETURN(startTime != 0xffffffff, false);
    PRECONDITION_RETURN(endTime != 0xffffffff, false);

    bool success = false;

    const uint32_t              startOffset  = 0xffffffff;
    const uint32_t              endOffset    = 0xffffffff;
    taglib_id3v2::ChapterFrame* chapterFrame = new taglib_id3v2::ChapterFrame(
        taglib::ByteVector::fromCString(id.c_str(), static_cast<unsigned int>(id.length())), startTime, endTime,
        startOffset, endOffset);
    if(chapterFrame != nullptr)
    {
        taglib_id3v2::TextIdentificationFrame* embeddedFrame = new taglib_id3v2::TextIdentificationFrame(
            taglib::ByteVector::fromCString("TIT2"), taglib::String::Type::UTF16);
        if(embeddedFrame != nullptr)
        {
            embeddedFrame->setTextEncoding(taglib::String::Type::UTF16);
            embeddedFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            chapterFrame->addEmbeddedFrame(embeddedFrame);
            context->Tags()->addFrame(chapterFrame);
            success = true;
        }
        else
        {
            SafeDelete(chapterFrame);
            success = false;
        }
    }

    return success;
}

bool ID3V2InsertChapterFrame(
    ID3V2Context* context, const UnicodeString& id, const UnicodeString& text, const uint32_t startTime,
    const uint32_t endTime, const UnicodeString& image, const UnicodeString& url)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);
    PRECONDITION_RETURN(text.empty() == false, false);
    PRECONDITION_RETURN(startTime != 0xffffffff, false);
    PRECONDITION_RETURN(endTime != 0xffffffff, false);

    size_t errorCount = 0;

    const uint32_t              startOffset   = 0xffffffff;
    const uint32_t              endOffset     = 0xffffffff;
    taglib_id3v2::ChapterFrame* pChapterFrame = new taglib_id3v2::ChapterFrame(
        taglib::ByteVector::fromCString(id.c_str(), static_cast<unsigned int>(id.length())), startTime, endTime,
        startOffset, endOffset);
    if(pChapterFrame != nullptr)
    {
        taglib_id3v2::TextIdentificationFrame* pTextIdFrame = new taglib_id3v2::TextIdentificationFrame(
            taglib::ByteVector::fromCString("TIT2"), taglib::String::Type::UTF16);
        if(pTextIdFrame != nullptr)
        {
            pTextIdFrame->setTextEncoding(taglib::String::Type::UTF16);
            pTextIdFrame->setText(taglib::String(text, taglib::String::Type::UTF8));
            pChapterFrame->addEmbeddedFrame(pTextIdFrame);

            if(image.empty() == false)
            {
                BinaryStream* pData = FileManager::ReadBinaryFile(image);
                if(pData != nullptr)
                {
                    uint8_t      imageHeader[10] = {0};
                    const size_t imageHeaderSize = 10;
                    if(pData->Read(0, imageHeader, imageHeaderSize) == true)
                    {
                        const UnicodeString mimeType = Picture::FormatString(imageHeader, imageHeaderSize);
                        if(mimeType.empty() == false)
                        {
                            taglib_id3v2::AttachedPictureFrame* pPictureFrame
                                = new taglib_id3v2::AttachedPictureFrame();
                            if(pPictureFrame != nullptr)
                            {
                                pPictureFrame->setMimeType(mimeType);
                                taglib::ByteVector coverData(
                                    (const char*)pData->Data(), (unsigned int)pData->DataSize());
                                pPictureFrame->setPicture(coverData);
                                pChapterFrame->addEmbeddedFrame(pPictureFrame);

                                if(url.empty() == false)
                                {
                                    taglib_id3v2::UrlLinkFrame* pUrlFrame
                                        = new taglib_id3v2::UrlLinkFrame(taglib::ByteVector::fromCString("WXXX"));
                                    if(pUrlFrame != nullptr)
                                    {
                                        pUrlFrame->setText("chapter");
                                        pUrlFrame->setUrl(url.c_str());
                                        pChapterFrame->addEmbeddedFrame(pUrlFrame);
                                    }
                                    else
                                    {
                                        errorCount++;
                                    }
                                }
                            }
                            else
                            {
                                errorCount++;
                            }
                        }
                        else
                        {
                            errorCount++;
                        }
                    }
                    else
                    {
                        errorCount++;
                    }

                    SafeRelease(pData);
                }
            }

            context->Tags()->addFrame(pChapterFrame);
        }
        else
        {
            errorCount++;
            SafeDelete(pChapterFrame);
        }
    }

    return 0 == errorCount;
}

bool ID3V2InsertTableOfContentsFrame(ID3V2Context* context, const UnicodeStringArray& tableOfContentsItems)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(tableOfContentsItems.empty() == false, false);

    bool success = false;

    taglib::ByteVector                  tableOfContentsId = taglib::ByteVector::fromCString("toc");
    taglib_id3v2::TableOfContentsFrame* tableOfContentsFrame
        = new taglib_id3v2::TableOfContentsFrame(tableOfContentsId);
    if(tableOfContentsFrame != 0)
    {
        tableOfContentsFrame->setIsTopLevel(true);
        tableOfContentsFrame->setIsOrdered(true);
        for(size_t j = 0; j < tableOfContentsItems.size(); j++)
        {
            tableOfContentsFrame->addChildElement(taglib::ByteVector::fromCString(tableOfContentsItems[j].c_str()));
        }

        context->Tags()->addFrame(tableOfContentsFrame);
        success = true;
    }

    return success;
}

bool ID3V2InsertCoverPictureFrame(ID3V2Context* context, const UnicodeString& image)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(image.empty() == false, false);

    bool success = false;

    taglib_id3v2::AttachedPictureFrame* pFrame = new taglib_id3v2::AttachedPictureFrame();
    if(pFrame != nullptr)
    {
        BinaryStream* pData = FileManager::ReadBinaryFile(image);
        if(pData != nullptr)
        {
            uint8_t      imageHeader[10] = {0};
            const size_t imageHeaderSize = 10;
            if(pData->Read(0, imageHeader, imageHeaderSize) == true)
            {
                const UnicodeString mimeType = Picture::FormatString(imageHeader, imageHeaderSize);
                if(mimeType.empty() == false)
                {
                    pFrame->setMimeType(mimeType);
                    taglib::ByteVector coverData((const char*)pData->Data(), (unsigned int)pData->DataSize());
                    pFrame->setPicture(coverData);
                    context->Tags()->addFrame(pFrame);
                    success = true;
                }
            }

            SafeRelease(pData);
        }
    }

    return success;
}

bool ID3V2QueryChapterFrames(ID3V2Context* pContext)
{
    PRECONDITION_RETURN(pContext != 0, false);
    PRECONDITION_RETURN(pContext->Tags() != 0, false);

    static const taglib::ByteVector CHAPTER_FRAME_ID = taglib::ByteVector::fromCString("CHAP", 4);
    static const taglib::ByteVector TEXT_FRAME_ID    = taglib::ByteVector::fromCString("TIT2", 4);

    taglib_id3v2::FrameList frames = pContext->Tags()->frameList();
    if(frames.isEmpty() == false)
    {
        taglib_id3v2::FrameList::Iterator frameIterator = frames.begin();
        while(frameIterator != frames.end())
        {
            taglib_id3v2::Frame* pFrame = *frameIterator;
            if(pFrame != nullptr)
            {
                if(pFrame->frameID() == CHAPTER_FRAME_ID)
                {
                    taglib_id3v2::ChapterFrame* pChapterFrame = reinterpret_cast<taglib_id3v2::ChapterFrame*>(pFrame);
                    if(pChapterFrame != nullptr)
                    {
                        taglib_id3v2::FrameList embeddedFrames = pChapterFrame->embeddedFrameList();
                        if(embeddedFrames.isEmpty() == false)
                        {
                            taglib_id3v2::FrameList::Iterator embeddedFrameIterator = embeddedFrames.begin();
                            while(embeddedFrameIterator != embeddedFrames.end())
                            {
                                taglib_id3v2::Frame* pEmbeddedFrame = *embeddedFrameIterator;
                                if(pEmbeddedFrame != nullptr)
                                {
                                    if(pEmbeddedFrame->frameID() == TEXT_FRAME_ID)
                                    {
                                        taglib_id3v2::TextIdentificationFrame* pTextIdFrame
                                            = reinterpret_cast<taglib_id3v2::TextIdentificationFrame*>(
                                                *embeddedFrameIterator);
                                        if(pTextIdFrame != nullptr)
                                        {
                                            taglib::StringList strings = pTextIdFrame->fieldList();
                                            if(strings.isEmpty() == false)
                                            {
                                                taglib::String str           = strings.front().to8Bit(true);
                                                UnicodeString  unicodeString = str.toCString();
                                                unicodeString                = unicodeString;
                                            }
                                        }
                                    }
                                }

                                embeddedFrameIterator++;
                            }
                        }
                    }
                }
            }

            frameIterator++;
        }
    }

    return true;
}

}} // namespace ultraschall::reaper
