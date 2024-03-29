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

#include "SaveChapterMarkersAction.h"
#include "CustomActionFactory.h"
#include "FileManager.h"
#include "NotificationStore.h"
#include "PlatformGateway.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SaveChapterMarkersAction> action;

ServiceStatus SaveChapterMarkersAction::Execute()
{
    PRECONDITION_RETURN(HasValidProject() == true, SERVICE_FAILURE);
    PRECONDITION_RETURN(ConfigureSources() == true, SERVICE_FAILURE);
    PRECONDITION_RETURN(ConfigureTargets() == true, SERVICE_FAILURE);

    ServiceStatus     status = SERVICE_FAILURE;
    NotificationStore supervisor(UniqueId());

    std::ostringstream os;
    for (size_t i = 0; i < chapterMarkers_.size(); i++) {
        const UnicodeString timestamp = SecondsToString(chapterMarkers_[i].Position());
        const UnicodeString item      = timestamp + " " + chapterMarkers_[i].Title();
        os << item << std::endl;
    }

    if (FileManager::WriteTextFile(target_, os.str()) == true) {
        status = SERVICE_SUCCESS;
    } else {
        supervisor.RegisterError("Failed to export chapter markers.");
    }

    return status;
}

bool SaveChapterMarkersAction::ConfigureTargets()
{
    bool              result = false;
    NotificationStore supervisor(UniqueId());

    const std::string targetDirectory = CurrentProjectDirectory();
    target_ = PlatformGateway::SelectChaptersFileName("Export chapter markers", targetDirectory, CurrentProjectName());
    if (target_.empty() == false) {
        result = true;
    }

    return result;
}

bool SaveChapterMarkersAction::ConfigureSources()
{
    bool              result = false;
    NotificationStore supervisor(UniqueId());

    ReaperProject currentProject = ReaperProject::Current();
    chapterMarkers_              = currentProject.ChapterMarkers();
    if (chapterMarkers_.empty() == false) {
        if (AreChapterMarkersValid(chapterMarkers_) == true) {
            result = true;
        } else {
            chapterMarkers_.clear();
            result = false;
        }
    } else {
        supervisor.RegisterWarning("No chapters have been set.");
        result = false;
    }

    return result;
}

}} // namespace ultraschall::reaper
