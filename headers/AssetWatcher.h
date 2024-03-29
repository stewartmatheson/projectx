#pragma once

#include <map>
#include <atomic>
#include <string>
#include <thread>

#include "SpriteSheet.h"

class AssetWatcher {
    std::thread watcher;
    void StartWatching();
    std::map<std::string, std::shared_ptr<SpriteSheet>> sprite_sheets;
    void Reload();
    std::atomic<bool> required_reload;
    std::atomic<bool> shutdown;

  public:
    void ReloadIfRequired();
    std::shared_ptr<SpriteSheet> GetSpriteSheet(std::string) const;
    void RegisterSpriteSheet(std::string, std::shared_ptr<SpriteSheet>);
    AssetWatcher(int);
    ~AssetWatcher();
};