#include <chrono>
#include <thread>

#include "AssetWatcher.h"

void AssetWatcher::StartWatching() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        required_reload = true;
    }
}
