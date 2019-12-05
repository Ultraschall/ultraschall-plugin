////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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
#include "PictureUtilities.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper { namespace id3v2 {

Context* StartTransaction(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);

    return new Context(targetName);
}

bool CommitTransaction(Context*& context)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);

    const bool success = context->Target()->save(taglib_mp3::File::ID3v2, true, 3);
    SafeDelete(context);

    return success;
}

void AbortTransaction(Context*& context)
{
    SafeDelete(context);
}

const char* QueryMIMEType(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, 0);
    PRECONDITION_RETURN(dataSize > 0, 0);

    const char* mimeType = 0;

    switch(QueryPictureFormat(data, dataSize))
    {
        case PICTURE_FORMAT::JPEG_PICTURE: {
            mimeType = "image/jpeg";
            break;
        }
        case PICTURE_FORMAT::PNG_PICTURE: {
            mimeType = "image/png";
            break;
        }
        default: {
            break;
        }
    }

    return mimeType;
}

void RemoveFrames(const UnicodeString& target, const UnicodeString& frameId)
{
    PRECONDITION(target.empty() == false);
    PRECONDITION(frameId.empty() == false);

    taglib_mp3::File mp3(target.c_str());
    if(mp3.isOpen() == true)
    {
        taglib_id3v2::Tag* id3v2 = mp3.ID3v2Tag();
        if(id3v2 != 0)
        {
            std::vector<taglib_id3v2::Frame*> foundFrames;

            taglib_id3v2::FrameList frames = id3v2->frameList(frameId.c_str());
            for(unsigned int i = 0; i < frames.size(); i++)
            {
                taglib_id3v2::Frame* frame = frames[i];
                if(frame != 0)
                {
                    foundFrames.push_back(frame);
                }
            }

            if(foundFrames.empty() == false)
            {
                for(size_t j = 0; j < foundFrames.size(); j++)
                {
                    id3v2->removeFrame(foundFrames[j]);
                }

                //            FIXME
                //            MP3_Commit(mp3);
            }
        }
    }
}

bool RemoveFrames(Context* context, const UnicodeString& id)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    std::vector<taglib_id3v2::Frame*> selectedFrames;

    taglib_id3v2::FrameList frames = context->Tags()->frameList(id.c_str());
    for(unsigned int i = 0; i < frames.size(); i++)
    {
        taglib_id3v2::Frame* frame = frames[i];
        if(frame != 0)
        {
            selectedFrames.push_back(frame);
        }
    }

    if(selectedFrames.empty() == false)
    {
        for(size_t j = 0; j < selectedFrames.size(); j++)
        {
            context->Tags()->removeFrame(selectedFrames[j]);
        }

        success = true;
    }

    return success;
}

bool InsertUTF16TextFrame(Context* context, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.size() == 4, false);

    bool success = false;

    RemoveFrames(context, id.c_str());

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

bool InsertUTF8TextFrame(Context* context, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    RemoveFrames(context, id.c_str());

    if(text.empty() == false)
    {
        taglib_id3v2::TextIdentificationFrame* textFrame = new taglib_id3v2::TextIdentificationFrame(
            taglib::ByteVector::fromCString(id.c_str()), taglib::String::Type::Latin1);
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

bool InsertTextFrame(Context* context, const UnicodeString& id, const UnicodeString& text, const CHAR_ENCODING encoding)
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

bool InsertCommentsFrame(Context* context, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    RemoveFrames(context, id.c_str());

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

bool InsertChapterFrame(
    Context* context, const UnicodeString& id, const UnicodeString& text, const uint32_t startTime,
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

bool InsertTableOfContentsFrame(Context* context, const UnicodeStringArray& tableOfContentsItems)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(tableOfContentsItems.empty() == false, false);

    bool success = false;

    RemoveFrames(context, "CTOC");

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

bool InsertCoverPictureFrame(Context* context, const UnicodeString& image)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(image.empty() == false, false);

    bool success = false;

    RemoveFrames(context, "APIC");

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
                const UnicodeString mimeType = QueryMIMEType(imageHeader, imageHeaderSize);
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

}}} // namespace ultraschall::reaper::id3v2
