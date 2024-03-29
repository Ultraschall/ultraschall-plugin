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

#include <string>
#include <vector>

#include "CustomActionFactory.h"
#include "FileManager.h"
#include "InsertMediaPropertiesAction.h"
#include "ITagWriter.h"
#include "NotificationStore.h"
#include "PlatformGateway.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "TagWriterFactory.h"
#include "TimeUtilities.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<InsertMediaPropertiesAction> action;

ServiceStatus InsertMediaPropertiesAction::Execute()
{
   PRECONDITION_RETURN(HasValidProject() == true, SERVICE_FAILURE);

   PRECONDITION_RETURN(ConfigureTargets() == true, SERVICE_FAILURE);
   PRECONDITION_RETURN(ConfigureSources() == true, SERVICE_FAILURE);

   ServiceStatus status = SERVICE_FAILURE;
   NotificationStore notificationStore(UniqueId());
   size_t errorCount = 0;

   for (size_t i = 0; i < targets_.size(); i++) {
      ITagWriter* pTagWriter = TagWriterFactory::Create(targets_[i]);
      if (pTagWriter != 0) {
         if (pTagWriter->Start(targets_[i]) == true) {
            const UnicodeStringArray missingMediaDataFields = FindMissingMediaData();
            const size_t missingFieldCount                  = missingMediaDataFields.size();
            static const size_t REQUIRED_MEDIA_DATA_FIELDS  = 6;
            if ((missingFieldCount > 0) && (missingFieldCount < REQUIRED_MEDIA_DATA_FIELDS)) {
               UnicodeStringStream os;
               os << "MP3 metadata is incomplete.";
               notificationStore.RegisterWarning(os.str());
            }
            else if (missingFieldCount == REQUIRED_MEDIA_DATA_FIELDS) {
               UnicodeStringStream os;
               os << "MP3 metadata is missing";
               notificationStore.RegisterWarning(os.str());
            }

            if (missingFieldCount < REQUIRED_MEDIA_DATA_FIELDS) {
               if (pTagWriter->InsertProperties(targets_[i], mediaData_) == false) {
                  UnicodeStringStream os;
                  os << "Failed to insert MP3 metadata into " << targets_[i] << ".";
                  notificationStore.RegisterError(os.str());
                  errorCount++;
               }
            }

            if (coverImage_.empty() == false) {
               if (pTagWriter->InsertCoverImage(targets_[i], coverImage_) == false) {
                  UnicodeStringStream os;
                  os << "Failed to insert cover image into " << targets_[i] << ".";
                  notificationStore.RegisterError(os.str());
                  errorCount++;
               }
            }
            else {
               UnicodeStringStream os;
               os << "The cover image is missing.";
               notificationStore.RegisterWarning(os.str());
            }

            if (chapterMarkers_.empty() == true) {
               UnicodeStringStream os;
               os << "The chapter markers are missing.";
               notificationStore.RegisterWarning(os.str());
            }
            else if (AreChapterMarkersValid(chapterMarkers_) == false) {
               UnicodeStringStream os;
               os << "One or more chapter markers are invalid.";
               notificationStore.RegisterError(os.str());
               errorCount++;
            }
            else {
               if (pTagWriter->InsertChapterMarkers(targets_[i], chapterMarkers_) == false) {
                  UnicodeStringStream os;
                  os << "Failed to insert chapter markers into " << targets_[i] << ".";
                  notificationStore.RegisterError(os.str());
                  errorCount++;
               }
            }

            pTagWriter->Stop(0 == errorCount);
         }

         SafeRelease(pTagWriter);
      }
   }

   if (0 == errorCount) {
      for (size_t i = 0; i < targets_.size(); i++) {
         UnicodeStringStream os;
         os << targets_[i] << " has been updated successfully.";
         notificationStore.RegisterSuccess(os.str());
      }

      status = SERVICE_SUCCESS;
   }

   return status;
}

bool InsertMediaPropertiesAction::ConfigureSources()
{
   bool result = true;

   mediaData_.clear();
   coverImage_.clear();
   chapterMarkers_.clear();

   mediaData_ = ReaperProject::Current().ProjectMetaData();
   if (mediaData_.find("coverImage") != mediaData_.end()) {
      coverImage_ = mediaData_.at("coverImage");
   }

   if (coverImage_.empty() == true) {
      coverImage_ = FindCoverImage();
   }

   chapterMarkers_ = CurrentProject().ChapterMarkers();
   if (chapterMarkers_.empty() == false) {
      bool errorFound = false;
      std::for_each(chapterMarkers_.begin(), chapterMarkers_.end(), [&](const ChapterTag& chapterMarker) {
         if (chapterMarker.Title().length() > Globals::MAX_CHAPTER_TITLE_LENGTH) {
            UnicodeStringStream os;
            os << "The chapter marker title '" << chapterMarker.Title() << "' is too long. "
               << "Make sure that is does not exceed " << Globals::MAX_CHAPTER_TITLE_LENGTH << " characters.";
            NotificationStore notificationStore(UniqueId());
            notificationStore.RegisterError(os.str());
            errorFound = true;
         }
      });

      result = (false == errorFound);
   }

   return result;
}

bool InsertMediaPropertiesAction::ConfigureTargets()
{
   NotificationStore supervisor(UniqueId());

   targets_.clear();

   static const UnicodeStringArray fileExtensions = {".mp3"};
   for (size_t i = 0; i < fileExtensions.size(); i++) {
      UnicodeString targetName = CreateProjectPath(fileExtensions[i]);
      if (FileManager::FileExists(targetName) != false) {
         targets_.push_back(targetName);
      }
   }

   if (targets_.empty() == true) {
      const UnicodeString target = PlatformGateway::SelectAudioFile("Select audio file");
      if (target.empty() == false) {
         targets_.push_back(target);
      }
   }

   return targets_.empty() == false;
}

UnicodeString InsertMediaPropertiesAction::FindCoverImage()
{
   UnicodeString result;
   const UnicodeStringArray extensions{".jpg", ".jpeg", ".png"};
   UnicodeStringArray files;
   for (size_t i = 0; i < extensions.size(); i++) {
      files.push_back("cover" + extensions[i]);
      files.push_back(CurrentProjectName() + extensions[i]);
   }
   const std::string coverImage = FileManager::FindFile(CurrentProjectDirectory(), files);
   if (coverImage.empty() == false) {
      result = FileManager::AppendPath(CurrentProjectDirectory(), coverImage);
   }
   return result;
}

UnicodeStringArray InsertMediaPropertiesAction::FindMissingMediaData()
{
   UnicodeStringArray missingMediaDataFields;

   static const UnicodeStringArray mediaDataKeys = {"podcast", "author", "episode", "category", "publicationDate", "description"};
   std::for_each(mediaDataKeys.begin(), mediaDataKeys.end(), [&](const UnicodeString& mediaDataKey) {
      const UnicodeStringDictionary::const_iterator mediaDataIterator = mediaData_.find(mediaDataKey);
      if (mediaDataIterator != mediaData_.end()) {
         const UnicodeString mediaDataField = UnicodeStringCopyTrimLeft(mediaDataIterator->second);
         if (mediaDataField.empty() == true) {
            missingMediaDataFields.push_back(mediaDataKey);
         }
         else if (mediaDataField[0] == '\n') {
            missingMediaDataFields.push_back(mediaDataKey);
         }
      }
      else {
         missingMediaDataFields.push_back(mediaDataKey);
      }
   });

   return missingMediaDataFields;
}

}} // namespace ultraschall::reaper
