#pragma once

#include <string>
#include <thread>

class AssetWatcher {

    std::thread watcher;
    void StartWatching();
  public:
    AssetWatcher(std::string);
};