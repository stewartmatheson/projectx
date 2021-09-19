#include <iostream>
#include <windows.h>

#include "AssetWatcher.h"

AssetWatcher::AssetWatcher(int scale)
    : watcher(&AssetWatcher::StartWatching, this), required_reload(false) {

    sprite_sheets["tile_map"] =
        std::make_shared<SpriteSheet>("./assets/house.png", scale, 16, 20, 20);

    sprite_sheets["entity_map"] = std::make_shared<SpriteSheet>(scale, 16);

    sprite_sheets["player_sprite_sheet"] = std::make_shared<SpriteSheet>(
        "./assets/NightThief.png", scale, 320, 1, 1);

    sprite_sheets["toolbar_sprite_sheet"] =
        std::make_shared<SpriteSheet>(scale, 8);
}

AssetWatcher::~AssetWatcher() { watcher.join(); }

std::shared_ptr<SpriteSheet>
AssetWatcher::GetSpriteSheet(std::string sprite_sheet_name) {
    return sprite_sheets[sprite_sheet_name];
}

void AssetWatcher::Reload() {
    for (auto const &sprite_sheet : sprite_sheets) {
        sprite_sheet.second->Reload();
    }
}

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
            1, directory_watcher_change_handles, false, 5000);

        if (directory_watch_wait_status == WAIT_OBJECT_0) {
            Sleep(10); // TODO : I think there is a race conidition here and the
                       // file is still locked
            required_reload = true;
        }
    }

    delete[] lp_asset_path;
}

void AssetWatcher::ReloadIfRequired() {
    if (required_reload) {
        Reload();
        required_reload = false;
    }
}
