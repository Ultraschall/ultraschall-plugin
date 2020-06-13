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
#include "Platform.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "NotificationStore.h"
#include "HttpClient.h"
#include "UpdateHandler.h"

namespace ultraschall { namespace reaper {

const UnicodeString UpdateHandler::LAST_UPDATE_CHECK_NAME = "last_update_check";
const double        UpdateHandler::ONE_DAY_IN_SECONDS     = 60.0 * 60.0 * 24.0;

bool UpdateHandler::IsUpdateCheckRequired()
{
    bool updateCheckRequired = false;

    const double lastUpdateTimestamp = ReadLastUpdateTimestamp();
    if(lastUpdateTimestamp > 0)
    {
        const double now   = QueryCurrentTimeAsSeconds();
        const double delta = (now - lastUpdateTimestamp);
        if(delta > ONE_DAY_IN_SECONDS) // standard timeout (24h)
        {
            updateCheckRequired = true;
        }
    }

    return updateCheckRequired;
}

void UpdateHandler::Check()
{
    if(true == IsUpdateCheckRequired())
    {
        HttpClient* pClient = new HttpClient();
        if(pClient != nullptr)
        {
            const std::string url           = "https://ultraschall.io/ultraschall_prerelease.txt";
            UnicodeString     remoteVersion = pClient->DownloadUrl(url);
            if(remoteVersion.empty() == false)
            {
                UnicodeStringTrim(remoteVersion);
                if(remoteVersion > ULTRASCHALL_VERSION)
                {
                    NotificationStore supervisor("ULTRASCHALL_UPDATE_CHECK");
                    std::string       message = "An update for Ultraschall is available. Go to "
                                          "https://ultraschall.fm/install to download the updated version ";
                    message += remoteVersion + ".";
                    supervisor.RegisterSuccess(message);
                }
            }

            SafeRelease(pClient);
        }

        const double lastUpdateTimestamp = QueryCurrentTimeAsSeconds();
        WriteLastUpdateTimestamp(lastUpdateTimestamp);
    }
}

bool UpdateHandler::WriteLastUpdateTimestamp(const double timestamp)
{
    PRECONDITION_RETURN(timestamp > 0, false);

    bool lastUpdateTimestampWritten = false;

    const std::string checkpoint = std::to_string(timestamp);
    if(checkpoint.empty() == false)
    {
        SystemProperty<std::string>::Save(UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME, checkpoint);
    }

    return lastUpdateTimestampWritten;
}

double UpdateHandler::ReadLastUpdateTimestamp()
{
    double lastUpdateTimestamp = -1;

    const double DEFAULT_TIMESTAMP = QueryCurrentTimeAsSeconds() - (ONE_DAY_IN_SECONDS + 1);

    if(SystemProperty<bool>::Query(UPDATE_SECTION_NAME, "update_check") == false)
    {
        WriteLastUpdateTimestamp(DEFAULT_TIMESTAMP);
    }

    if(SystemProperty<bool>::Query(UPDATE_SECTION_NAME, "update_check") == true)
    {
        if(SystemProperty<std::string>::Exists(UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME) == true)
        {
            const std::string previousUpdateCheckpoint =
                SystemProperty<std::string>::Query(UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME);
            if(previousUpdateCheckpoint.empty() == false)
            {
                try
                {
                    lastUpdateTimestamp = std::stod(previousUpdateCheckpoint);
                }
                catch(
                    std::invalid_argument&) // inconsistency in reaper-extstate.ini (number format), force update check
                {
                    lastUpdateTimestamp = DEFAULT_TIMESTAMP;
                }
                catch(std::out_of_range&) // inconsistency in reaper-extstate.ini (overflow), force update check
                {
                    lastUpdateTimestamp = DEFAULT_TIMESTAMP;
                }
            }
            else // inconsistency in reaper-extstate.ini, force update check
            {
                lastUpdateTimestamp = DEFAULT_TIMESTAMP;
            }
        }
        else // initial status, force update check
        {
            lastUpdateTimestamp = DEFAULT_TIMESTAMP;
        }
    }

    return lastUpdateTimestamp;
}

double UpdateHandler::QueryCurrentTimeAsSeconds()
{
    const std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    const std::chrono::duration<double>                      seconds =
        std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch());
    return seconds.count();
}

}} // namespace ultraschall::reaper
