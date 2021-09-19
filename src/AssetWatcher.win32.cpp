#include <windows.h>

#include "AssetWatcher.h"

void AssetWatcher::StartWatching() {
    std::string asset_path =
        "C:\\Users\\Stewart\\SourceCode\\projectx\\build\\assets";
    HANDLE directory_watcher_change_handles[1];
    LPTSTR lp_asset_path = new TCHAR[asset_path.size() + 1];
    DWORD directory_watch_wait_status;
    strcpy(lp_asset_path, asset_path.c_str());

    while (true) {
        directory_watcher_change_handles[0] = FindFirstChangeNotification(
            lp_asset_path, false, FILE_NOTIFY_CHANGE_LAST_WRITE);

        if (directory_watcher_change_handles[0] == INVALID_HANDLE_VALUE) {
            exit(GetLastError());
        }

        directory_watch_wait_status = WaitForMultipleObjects(
            1, directory_watcher_change_handles, false, INFINITE);

        if (directory_watch_wait_status == WAIT_OBJECT_0) {
            Sleep(10); // TODO : I think there is a race conidition here and the
                       // file is still locked
            required_reload = true;
        }
    }

    delete[] lp_asset_path;
}
