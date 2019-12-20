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

#include "FileDialog.h"
#include "ReaperGateway.h"
#include "StringUtilities.h"

#include <gtk/gtk.h>

namespace ultraschall { namespace reaper {

FileDialog::FileDialog(const UnicodeString& caption, const UnicodeString& initialDirectory) {}

FileDialog::~FileDialog() {}

UnicodeString FileDialog::SelectChaptersFile()
{
    UnicodeString result;

    GtkWindow*           pParent = (GtkWindow*)ReaperGateway::View();
    GtkFileChooserAction action  = GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget*           pDialog = gtk_file_chooser_dialog_new(
        caption_.c_str(), pParent, action, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    if(pDialog != nullptr)
    {
        GtkFileChooser* pChooser = GTK_FILE_CHOOSER(pDialog);
        if(pChooser != nullptr)
        {
            GtkFileFilter* pFilter = gtk_file_filter_new();
            if(pFilter != nullptr)
            {
                gtk_file_filter_add_pattern(pFilter, "*.chapters.txt");
                gtk_file_filter_add_pattern(pFilter, "*.mp4chaps");
                gtk_file_chooser_set_filter(pChooser, pFilter);

                const gint dialogResult = gtk_dialog_run(GTK_DIALOG(pDialog));
                if(dialogResult == GTK_RESPONSE_ACCEPT)
                {
                    char* filename = gtk_file_chooser_get_filename(pChooser);
                    if(filename != nullptr)
                    {
                        result = filename;
                        g_free(filename);
                    }
                }

                g_free(pFilter);
            }
        }

        gtk_widget_destroy(pDialog);
    }

    return result;
}

UnicodeString FileDialog::SelectAudioFile()
{
    UnicodeString result;

    GtkWindow*           pParent = (GtkWindow*)ReaperGateway::View();
    GtkFileChooserAction action  = GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget*           pDialog = gtk_file_chooser_dialog_new(
        caption_.c_str(), pParent, action, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    if(pDialog != nullptr)
    {
        GtkFileChooser* pChooser = GTK_FILE_CHOOSER(pDialog);
        if(pChooser != nullptr)
        {
            GtkFileFilter* pFilter = gtk_file_filter_new();
            if(pFilter != nullptr)
            {
                gtk_file_filter_add_pattern(pFilter, "*.mp3");
                gtk_file_chooser_set_filter(pChooser, pFilter);

                const gint dialogResult = gtk_dialog_run(GTK_DIALOG(pDialog));
                if(dialogResult == GTK_RESPONSE_ACCEPT)
                {
                    char* filename = gtk_file_chooser_get_filename(pChooser);
                    if(filename != nullptr)
                    {
                        result = filename;
                        g_free(filename);
                    }
                }

                g_free(pFilter);
            }
        }

        gtk_widget_destroy(pDialog);
    }

    return result;
}

UnicodeString FileDialog::SelectPictureFile()
{
    UnicodeString result;

    GtkWindow*           pParent = (GtkWindow*)ReaperGateway::View();
    GtkFileChooserAction action  = GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget*           pDialog = gtk_file_chooser_dialog_new(
        caption_.c_str(), pParent, action, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    if(pDialog != nullptr)
    {
        GtkFileChooser* pChooser = GTK_FILE_CHOOSER(pDialog);
        if(pChooser != nullptr)
        {
            GtkFileFilter* pFilter = gtk_file_filter_new();
            if(pFilter != nullptr)
            {
                gtk_file_filter_add_pattern(pFilter, "*.jpg");
                gtk_file_filter_add_pattern(pFilter, "*.jpeg");
                gtk_file_filter_add_pattern(pFilter, "*.png");
                gtk_file_chooser_set_filter(pChooser, pFilter);

                const gint dialogResult = gtk_dialog_run(GTK_DIALOG(pDialog));
                if(dialogResult == GTK_RESPONSE_ACCEPT)
                {
                    char* filename = gtk_file_chooser_get_filename(pChooser);
                    if(filename != nullptr)
                    {
                        result = filename;
                        g_free(filename);
                    }
                }

                g_free(pFilter);
            }
        }

        gtk_widget_destroy(pDialog);
    }

    return result;
}

UnicodeString FileDialog::ChooseChaptersFileName()
{
    UnicodeString result;

    GtkWindow*           pParent = (GtkWindow*)ReaperGateway::View();
    GtkFileChooserAction action  = GTK_FILE_CHOOSER_ACTION_SAVE;
    GtkWidget*           pDialog = gtk_file_chooser_dialog_new(
        caption_.c_str(), pParent, action, "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
    if(pDialog != nullptr)
    {
        GtkFileChooser* pChooser = GTK_FILE_CHOOSER(pDialog);
        if(pChooser != nullptr)
        {
            GtkFileFilter* pFilter = gtk_file_filter_new();
            if(pFilter != nullptr)
            {
                gtk_file_filter_add_pattern(pFilter, "*.chapters.txt");
                gtk_file_filter_add_pattern(pFilter, "*.mp4chaps");
                gtk_file_chooser_set_filter(pChooser, pFilter);

                const gint dialogResult = gtk_dialog_run(GTK_DIALOG(pDialog));
                if(dialogResult == GTK_RESPONSE_ACCEPT)
                {
                    char* filename = gtk_file_chooser_get_filename(pChooser);
                    if(filename != nullptr)
                    {
                        result = filename;
                        g_free(filename);
                    }
                }

                g_free(pFilter);
            }
        }

        gtk_widget_destroy(pDialog);
    }

    return result;
}

}} // namespace ultraschall::reaper
