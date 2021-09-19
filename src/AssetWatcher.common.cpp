#include <filesystem>
#include <iostream>

#include "AssetWatcher.h"

AssetWatcher::AssetWatcher(int scale)
    : watcher(&AssetWatcher::StartWatching, this), required_reload(false),
      shutdown(false) {

    sprite_sheets["tile_map"] =
        std::make_shared<SpriteSheet>("./assets/house.png", scale, 16, 20, 20);

    sprite_sheets["entity_map"] = std::make_shared<SpriteSheet>(scale, 16);

    sprite_sheets["player_sprite_sheet"] = std::make_shared<SpriteSheet>(
        "./assets/NightThief.png", scale, 320, 1, 1);

    sprite_sheets["toolbar_sprite_sheet"] =
        std::make_shared<SpriteSheet>(scale, 8);
}

AssetWatcher::~AssetWatcher() {
    shutdown = true;
    watcher.join();
}

std::shared_ptr<SpriteSheet>
AssetWatcher::GetSpriteSheet(std::string sprite_sheet_name) {
    return sprite_sheets[sprite_sheet_name];
}

void AssetWatcher::Reload() {
    for (auto const &sprite_sheet : sprite_sheets) {
        sprite_sheet.second->Reload();
    }
}

void AssetWatcher::ReloadIfRequired() {
    if (required_reload) {
        Reload();
        required_reload = false;
    }
}
