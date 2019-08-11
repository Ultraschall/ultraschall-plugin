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

// clang-format off
#include <windows.h>
#include <commctrl.h>
// clang-format on

#include "resource.h"

#include "Common.h"
#include "Application.h"
#include "UIMessageDialog.h"
#include "ReaperEntryPoints.h"

namespace ultraschall { namespace reaper {

#ifdef ULTRASCHALL_BROADCASTER
static const bool forceDisplay = false;
#else  // #ifndef ULTRASCHALL_BROADCASTER
static const bool forceDisplay = true;
#endif // #ifndef ULTRASCHALL_BROADCASTER

class UIMessageDisplay
{
public:
    UIMessageDisplay(const UIMessageArray& messages);

    void Show();

private:
    static const UnicodeString UI_MESSAGE_DIALOG_CAPTION;

    const UIMessageArray& messages_;

    static INT_PTR DialogProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

    static UnicodeString StringFromMessageSeverity(const UIMessageClass severity);
    static COLORREF      ColorFromMessageSeverity(const UIMessageClass severity);

    
private:
    static UIMessageClass MaxSeverity(const UIMessageArray* pItems);
};

const UnicodeString UIMessageDisplay::UI_MESSAGE_DIALOG_CAPTION("Ultraschall");

UIMessageDisplay::UIMessageDisplay(const UIMessageArray& messages) : messages_(messages) {}

void UIMessageDisplay::Show()
{
    if(messages_.empty() == false)
    {
        Application& application = Application::Instance();
        DialogBoxParam(
            (HINSTANCE)application.Handle(), MAKEINTRESOURCE(IDD_MESSAGE_DIALOG), 0, (DLGPROC)DialogProc,
            (LPARAM)&messages_);
    }
}

INT_PTR UIMessageDisplay::DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND            hwndDialog        = 0;
    static HWND            hwndListView      = 0;
    static HBRUSH          hDialogForeground = 0;
    static HBRUSH          hDialogBackground = 0;
    static UIMessageArray* pItems            = 0;

    switch(message)
    {
        case WM_INITDIALOG:
        {
            hwndDialog   = hwnd;
            hwndListView = GetDlgItem(hwndDialog, IDC_MESSAGE_LIST);
            pItems       = (UIMessageArray*)lParam;

            hDialogForeground = CreateSolidBrush(RGB(244, 247, 255));
            hDialogBackground        = CreateSolidBrush(RGB(43, 43, 43));

            ListView_SetTextColor(hwndListView, RGB(244, 247, 255));
            COLORREF backgroundColor = ColorFromMessageSeverity(MaxSeverity(pItems));
            ListView_SetTextBkColor(hwndListView, backgroundColor);
            //ListView_SetTextBkColor(hwndListView, RGB(43, 43, 43));
            ListView_SetBkColor(hwndListView, RGB(43, 43, 43));

            int                iColumn                              = 0;
            static const int   MAX_LIST_VIEW_COLUMNS                = 3;
            static const LPSTR columnLabels[MAX_LIST_VIEW_COLUMNS]  = {"#", "Severity", "Message"};
            static const int   columnFormats[MAX_LIST_VIEW_COLUMNS] = {LVCFMT_RIGHT, LVCFMT_LEFT, LVCFMT_LEFT};
            static const int   columnSizes[MAX_LIST_VIEW_COLUMNS]   = {20, 100, 600};
            for(int i = 0; i < MAX_LIST_VIEW_COLUMNS; i++)
            {
                LVCOLUMN columnHeader = {0};
                columnHeader.mask     = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                columnHeader.iSubItem = i;
                columnHeader.pszText  = columnLabels[i];
                columnHeader.fmt      = columnFormats[i];
                columnHeader.cx       = columnSizes[i];
                ListView_InsertColumn(hwndListView, i, &columnHeader);
            }

            for(int i = 0; i < (int)pItems->size(); i++)
            {
                LVITEM item         = {0};
                item.mask           = LVIF_TEXT;
                item.iItem          = i;
                char itemBuffer[20] = {0};
                sprintf(itemBuffer, "%d", i);
                item.pszText = (LPSTR)itemBuffer;
                ListView_InsertItem(hwndListView, &item);

                std::string severityString = (LPSTR)(U2H(StringFromMessageSeverity((*pItems)[i].Severity()))).c_str();
                ListView_SetItemText(hwndListView, i, 1, (LPSTR)severityString.c_str());

                std::string messageString = (LPSTR)U2H((*pItems)[i].Str()).c_str();
                ListView_SetItemText(hwndListView, i, 2, (LPSTR)messageString.c_str());
            }

            return TRUE;
        }

        case WM_CTLCOLORDLG:
            return (INT_PTR)hDialogBackground;

        case WM_CLOSE:
            DeleteObject(hDialogBackground);
            hDialogBackground = 0;

            DeleteObject(hDialogForeground);
            hDialogForeground = 0;

            pItems = 0;

            hwndListView = 0;
            hwndDialog   = 0;

            DestroyWindow(hwnd);

            return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(lParam))
            {
                case IDOK:
                case IDCANCEL:
                    DeleteObject(hDialogBackground);
                    hDialogBackground = 0;

                    DeleteObject(hDialogForeground);
                    hDialogForeground = 0;

                    pItems = 0;

                    hwndListView = 0;
                    hwndDialog   = 0;

                    EndDialog(hwnd, 0);
                    return TRUE;

                default:
                    return FALSE;
            }
            break;
        }
    }

    return FALSE;
}

UnicodeString UIMessageDisplay::StringFromMessageSeverity(const UIMessageClass severity)
{
    switch(severity)
    {
        case UIMessageClass::MESSAGE_SUCCESS:
            return "Success";
        case UIMessageClass::MESSAGE_WARNING:
            return "Warning";
        case UIMessageClass::MESSAGE_ERROR:
            return "Error";
        case UIMessageClass::MESSAGE_FATAL_ERROR:
            return "Fatal Error";
        default:
            return "<Unknown>";
    }
}

COLORREF UIMessageDisplay::ColorFromMessageSeverity(const UIMessageClass severity)
{
    switch(severity)
    {
        case UIMessageClass::MESSAGE_SUCCESS:
            return RGB(0, 128, 0);
        case UIMessageClass::MESSAGE_WARNING:
            return RGB(255, 140, 0);
        case UIMessageClass::MESSAGE_ERROR:
            return RGB(128, 0, 0);
        case UIMessageClass::MESSAGE_FATAL_ERROR:
            return RGB(128, 0, 128);
        default:
            return RGB(0, 0, 0);
    }
}

UIMessageClass UIMessageDisplay::MaxSeverity(const UIMessageArray* pItems)
{
    PRECONDITION_RETURN(pItems != 0, UIMessageClass::INVALID_MESSAGE_CLASS);
    PRECONDITION_RETURN(pItems->empty() == false, UIMessageClass::INVALID_MESSAGE_CLASS);

    UIMessageClass maxSeverity = UIMessageClass::MESSAGE_SUCCESS;
    for(size_t i = 0; i < pItems->size(); i++)
    {
        const UIMessage& message = (*pItems)[i];
        if(message.Severity() > maxSeverity)
        {
            maxSeverity = message.Severity();
        }
    }

    return maxSeverity;
}

UIMessageDialog::UIMessageDialog() {}

int UIMessageDialog::Display(const UIMessageArray& items, const UIMessageClass& severityThreshold)
{
    if(true == forceDisplay)
    {
        return ForceDisplay(items, severityThreshold);
    }

    return 0;
}

int UIMessageDialog::ForceDisplay(const UIMessageArray& items, const UIMessageClass& severityThreshold)
{
    PRECONDITION_RETURN(items.empty() == false, 0);

    UIMessageDisplay messageDisplay(items);
    messageDisplay.Show();
    return 0;
}

}} // namespace ultraschall::reaper
