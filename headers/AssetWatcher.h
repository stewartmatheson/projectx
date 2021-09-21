#pragma once

#include <atomic>
#include <string>
#include <thread>
#include <map>

#include "SpriteSheet.h"


class AssetWatcher {
    std::thread watcher;
    void StartWatching();
    std::map<std::string, std::shared_ptr<SpriteSheet>> sprite_sheets;
    void Reload();
    std::atomic<bool> required_reload;
  public:
    void ReloadIfRequired();
    std::shared_ptr<SpriteSheet> GetSpriteSheet(std::string);
    AssetWatcher(int);
    ~AssetWatcher();
};