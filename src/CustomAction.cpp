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

#include "CustomAction.h"
#include "FileManager.h"
#include "StringUtilities.h"
#include "NotificationStore.h"

namespace ultraschall { namespace reaper {

bool CustomAction::IsValidCustomActionId(const int32_t id)
{
    return id != INVALID_CUSTOM_ACTION_ID;
}

bool CustomAction::HasValidProject()
{
    NotificationStore supervisor("ProjectDirty");

    const bool isValid = (CurrentProjectDirectory().empty() == false) && (CurrentProjectName().empty() == false);
    if(isValid == false)
    {
        supervisor.RegisterError("This action requires that you save the current project. Save the current project and "
                                 "execute the current action again.");
    }

    return isValid;
}

ReaperProject CustomAction::CurrentProject() 
{
  return ReaperProject::Current();
}

UnicodeString CustomAction::CurrentProjectDirectory()
{
    return CurrentProject().FolderName();
}

UnicodeString CustomAction::CurrentProjectName()
{
    return CurrentProject().Name();
}

UnicodeString CustomAction::CreateProjectPath(const UnicodeString& extension)
{
    PRECONDITION_RETURN(HasValidProject() == true, UnicodeString());

    UnicodeString path = FileManager::AppendPath(CurrentProjectDirectory(), CurrentProjectName());
    if(extension.empty() == false)
    {
        path += extension;
    }

    return path;
}

bool CustomAction::AreChapterMarkersValid(const MarkerArray& markers)
{
    PRECONDITION_RETURN(HasValidProject() == true, false);

    NotificationStore supervisor("ChapterMarkerOutOfRange");

    bool valid = true;

    for(size_t i = 0; i < markers.size(); i++)
    {
        const ChapterTag&       current      = markers[i];
        const UnicodeString safeName     = current.Title();
        const double        safePosition = current.Position();

        if(CurrentProject().IsValidPosition(current.Position()) == false)
        {
            UnicodeStringStream os;
            os << "The chapter marker '" << ((safeName.empty() == false) ? safeName : UnicodeString("Unknown"))
               << "' is out of track range.";
            supervisor.RegisterError(os.str());
            valid = false;
        }

        if(current.Title().empty() == true)
        {
            UnicodeStringStream os;
            os << "The Chapter marker at '" << SecondsToString(safePosition) << "' has no name.";
            supervisor.RegisterError(os.str());
            valid = false;
        }
    }

    return valid;
}

}} // namespace ultraschall::reaper
