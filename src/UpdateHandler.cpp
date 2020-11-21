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

#include "Common.h"
#include "PlatformGateway.h"
#include "StringUtilities.h"
#include "ProfileProperties.h"
#include "NotificationStore.h"
#include "HttpClient.h"
#include "UpdateHandler.h"

namespace ultraschall { namespace reaper {

const UnicodeString UpdateHandler::CHECK_ENABLED_PROFILE_NAME =
    "/Users/heiko/Library/Application Support/REAPER/ultraschall-settings.ini";
const UnicodeString UpdateHandler::CHECK_ENABLED_SECTION_NAME = "ultraschall_settings_updatecheck";
const UnicodeString UpdateHandler::CHECK_ENABLED_VALUE_NAME   = "Value";

const UnicodeString UpdateHandler::LAST_CHECKPOINT_PROFILE_NAME = "ultraschall.ini";
const UnicodeString UpdateHandler::LAST_CHECKPOINT_SECTION_NAME = "update_check";
const UnicodeString UpdateHandler::LAST_CHECKPOINT_VALUE_NAME   = "last_checkpoint";

const double UpdateHandler::ONE_DAY_IN_SECONDS = 60.0 * 60.0 * 24.0;

bool UpdateHandler::IsUpdateCheckRequired()
{
    bool updateCheckRequired = false;

    if(ProfileProperty<bool>::Exists(
           CHECK_ENABLED_PROFILE_NAME, CHECK_ENABLED_SECTION_NAME, CHECK_ENABLED_VALUE_NAME) == true)
    {
        if(ProfileProperty<bool>::Query(
               CHECK_ENABLED_PROFILE_NAME, CHECK_ENABLED_SECTION_NAME, CHECK_ENABLED_VALUE_NAME) == true)
        {
            const double lastUpdateTimestamp = ReadLastUpdateTimestamp();
            if(lastUpdateTimestamp > 0)
            {
                const double now   = QueryCurrentTimeAsSeconds();
                const double delta = (now - lastUpdateTimestamp);
                if(delta >= ONE_DAY_IN_SECONDS) // default timeout (24h)
                {
                    updateCheckRequired = true;
                }
            }
            else // first run
            {
                updateCheckRequired = true;
            }
        }
    }

    return updateCheckRequired;
}

void UpdateHandler::Check()
{
    PRECONDITION(IsUpdateCheckRequired() == true);

    HttpClient* pClient = new HttpClient();
    if(pClient != nullptr)
    {
        bool                     downloadSucceeded = false;
        const UnicodeStringArray urls              = DownloadServers();
        for(size_t i = 0; (downloadSucceeded == false) && (i < urls.size()); i++)
        {
            const UnicodeString url           = urls[i];
            UnicodeString       remoteVersion = pClient->DownloadUrl(url);
            if(remoteVersion.empty() == false)
            {
                downloadSucceeded = true;

                UnicodeStringTrim(remoteVersion);
                // TODO To be honst, this comparison needs more work
                if(remoteVersion > ULTRASCHALL_VERSION)
                {
                    NotificationStore supervisor("ULTRASCHALL_UPDATE_CHECK");
                    UnicodeString     message = "An update for Ultraschall is available. Go to "
                                            "https://ultraschall.fm/install to download the updated version ";
                    message += remoteVersion + ".";
                    supervisor.RegisterSuccess(message);
                }
            }
        }

        SafeRelease(pClient);

        if(true == downloadSucceeded)
        {
            const double lastUpdateTimestamp = QueryCurrentTimeAsSeconds();
            WriteLastUpdateTimestamp(lastUpdateTimestamp);
        }
    }
}

bool UpdateHandler::WriteLastUpdateTimestamp(const double timestamp)
{
    PRECONDITION_RETURN(timestamp > 0, false);

    bool lastUpdateTimestampWritten = false;

    const UnicodeString checkpoint = std::to_string(timestamp);
    if(checkpoint.empty() == false)
    {
        ProfileProperty<UnicodeString>::Save(
            LAST_CHECKPOINT_PROFILE_NAME, LAST_CHECKPOINT_SECTION_NAME, LAST_CHECKPOINT_VALUE_NAME, checkpoint);
    }

    return lastUpdateTimestampWritten;
}

double UpdateHandler::ReadLastUpdateTimestamp()
{
    static const double INVALID_TIMESTAMP   = -1;
    double              lastUpdateTimestamp = INVALID_TIMESTAMP;

    if(ProfileProperty<UnicodeString>::Exists(
           LAST_CHECKPOINT_PROFILE_NAME, LAST_CHECKPOINT_SECTION_NAME, LAST_CHECKPOINT_VALUE_NAME) == true)
    {
        const UnicodeString previousUpdateCheckpoint = ProfileProperty<UnicodeString>::Query(
            LAST_CHECKPOINT_PROFILE_NAME, LAST_CHECKPOINT_SECTION_NAME, LAST_CHECKPOINT_VALUE_NAME);
        if(previousUpdateCheckpoint.empty() == false)
        {
            try
            {
                lastUpdateTimestamp = std::stod(previousUpdateCheckpoint);
            }
            catch(std::invalid_argument&) // inconsistency in reaper-extstate.ini (number format), force update check
            {
                lastUpdateTimestamp = INVALID_TIMESTAMP;
            }
            catch(std::out_of_range&) // inconsistency in reaper-extstate.ini (overflow), force update check
            {
                lastUpdateTimestamp = INVALID_TIMESTAMP;
            }
        }
        else // inconsistency in reaper-extstate.ini, force update check
        {
            lastUpdateTimestamp = INVALID_TIMESTAMP;
        }
    }
    else // initial status, force update check
    {
        lastUpdateTimestamp = INVALID_TIMESTAMP;
    }

    return lastUpdateTimestamp;
} // namespace reaper

double UpdateHandler::QueryCurrentTimeAsSeconds()
{
    const std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    const std::chrono::duration<double>                      seconds =
        std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch());
    return seconds.count();
}

UnicodeStringArray UpdateHandler::DownloadServers()
{
    const UnicodeStringArray urls = {
        "https://ultraschall.io/ultraschall_prerelease.txt", "https://ultraschall.fm/ultraschall_prerelease.txt"};
    return urls;
}

}} // namespace ultraschall::reaper
