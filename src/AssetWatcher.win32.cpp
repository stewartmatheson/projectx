#include <filesystem>
#include <windows.h>

#include "AssetWatcher.h"

void AssetWatcher::StartWatching() {
    auto asset_path = std::filesystem::absolute("assets");

    while (!shutdown) {
        auto directory_watcher_change_handle = FindFirstChangeNotification(
            asset_path.string().c_str(), false, FILE_NOTIFY_CHANGE_LAST_WRITE);

        if (directory_watcher_change_handle == INVALID_HANDLE_VALUE) {
            exit(GetLastError());
        }

        auto directory_watch_wait_status =
            WaitForSingleObject(directory_watcher_change_handle, 5000);

        if (directory_watch_wait_status == WAIT_OBJECT_0) {
            Sleep(10); // TODO : I think there is a race conidition here and the
                       // file is still locked
            required_reload = true;
        }
    }
}
