# How the update check works

`UpdateHandler::Check()` is a one-shot, blocking HTTP request that runs while REAPER loads the plugin. It reads a version string from the Ultraschall website and, if that version is newer than the compiled-in one, leaves a message for someone else to show. The plugin never shows a dialog itself.

## How it gets called

REAPER calls the plugin entry point in `src/reaper_ultraschall.cpp`. That calls `Application::Start()`, which runs the check at `src/Application.cpp:55` while holding `lock_`. The custom actions are registered only after `Start()` returns. So until the check finishes, plugin startup waits and nothing else happens.

## Step 1: deciding whether to check

`Check()` begins with `PRECONDITION(IsUpdateCheckRequired() == true)`. That macro is just an early `return` (`src/Common.h:65`), so a "no" means the function quietly does nothing.

`IsUpdateCheckRequired()` in `src/UpdateHandler.cpp` checks two INI files in REAPER's resource directory:

1. `ultraschall-settings.ini`, section `[ultraschall_settings_updatecheck]`, key `Value`. If the key is missing, there's no check. The check is opt-in, and something outside this plugin, probably the Ultraschall Lua settings UI, has to write `true` or a nonzero number there.
2. `ultraschall.ini`, section `[update_check]`, key `last_checkpoint`. This holds a Unix timestamp in seconds, stored as a double. If the value is missing, empty or unparsable, `ReadLastUpdateTimestamp()` returns -1 and the code treats it as a first run. Otherwise it checks only when 24 hours or more have passed.

Both files go through `GetPrivateProfileString`/`WritePrivateProfileString` via `ReaperGateway`, and the path comes from `PlatformGateway::QueryReaperProfilePath()`.

## Step 2: fetching the remote version

`DownloadServerUrls()` returns two URLs, tried in order:

- `https://ultraschall.io/current_release.txt`
- `https://ultraschall.fm/current_release.txt`

The loop stops at the first URL that returns a non-empty body. `HttpClient::ReadString()` is a thin libcurl wrapper. It follows redirects, has a 3-second connect timeout and writes into a `SequentialStream`. On `CURLE_OK` it turns the buffer into a string. Any curl error gives back an empty string, and the loop moves on to the next URL.

## Step 3: comparing versions

`SanitizeVersionString()` trims whitespace and keeps only the first line. The `Version` class splits on `.` and parses major, minor and patch with `std::stoi`. A missing or non-numeric part becomes 0. The local version is the `ULTRASCHALL_VERSION` macro, currently `"5.1.0"` in `src/Common.h`. Comparison is lexicographic on those three integers.

## Step 4: notifying

If local < remote, the code creates a `NotificationStore` with context `ULTRASCHALL_UPDATE_CHECK` and registers a "success" message pointing to `https://ultraschall.fm/install`. The store sends its messages from its destructor, so they go out when the `if` block closes.

Sending means writing to REAPER's ExtState, section `ultraschall_messages`. The code bumps `message_count` and writes `message_N = "+;ULTRASCHALL_UPDATE_CHECK;<text>"`. It uses `SetExtState(..., persist=false)`, so the message lasts only for the current REAPER session. `NotificationStore::DisplayNotifications()` is a `// TODO: Call LUA action`. The Ultraschall Lua scripts presumably poll that section and show the message. Nothing in this repo reads it.

## Step 5: recording the timestamp

The timestamp is written only when `messageDispatched` is true, meaning only when an update was actually found.

## Known issues

Some of these look like real bugs, not style complaints.

- **Users who are up to date get checked on every launch.** Because of step 5, the 24-hour throttle only applies once an update exists. A user on the latest version never gets a `last_checkpoint`, so every REAPER start makes a network request. The intent was probably to write the timestamp after any successful download. Moving the write to depend on `downloadSucceeded` would do that.
- **REAPER startup can hang.** `CURLOPT_CONNECTTIMEOUT` only limits the TCP/TLS connect. There's no `CURLOPT_TIMEOUT`, so a server that accepts the connection and then stalls blocks REAPER's load with no limit. Offline, the worst case is about 6 seconds for both URLs, plus DNS time. Because this runs on the main thread inside the entry point, a worker thread or a total timeout would help.
- **HTTP errors count as success.** Without `CURLOPT_FAILONERROR`, a 404 or 500 still returns `CURLE_OK` with an HTML body. The loop sees a non-empty string, sets `downloadSucceeded`, and never tries the fallback URL. The HTML parses as version 0.0.0, so no notification goes out either. The fallback mirror only helps when the first host is completely unreachable.
- **`SanitizeVersionString` mixes two strings.** It finds the newline position in the trimmed `result` but calls `substr` on the original `versionString`. With leading whitespace, the cut lands in the wrong place. `result.substr(...)` fixes it.
- **`WriteLastUpdateTimestamp` always returns `false`.** It never sets `lastUpdateTimestampWritten`. No caller checks the result today, so this is harmless for now.
- **The comments in `ReadLastUpdateTimestamp` mention `reaper-extstate.ini`**, but the value lives in `ultraschall.ini`.
