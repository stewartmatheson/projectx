#pragma once


#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "EventWithMouse.h"
#include "HouseSceneReducer.h"
#include "ViewLayer.h"
#include "AssetWatcher.h"
#include "Controller.h"

typedef std::shared_ptr<std::unordered_map<EntityState, Animation>>
    AnimationMap;

struct TimedController {
    sf::Clock timer;
    std::shared_ptr<Controller<HouseSceneReducer>> controller;
    TimedController(std::shared_ptr<Controller<HouseSceneReducer>> controller)
        : controller(controller) {}
};

class HouseScene {
    std::shared_ptr<AssetWatcher> asset_watcher;
    std::vector<std::shared_ptr<TimedController>> timed_controllers;
    std::list<std::shared_ptr<ViewLayer>> view_layers;
    AnimationMap animations;
    std::shared_ptr<HouseSceneReducer> reducer;
  public:
    HouseScene(std::shared_ptr<AssetWatcher>, std::vector<std::shared_ptr<TimedController>>, std::list<std::shared_ptr<ViewLayer>>,
               AnimationMap, std::shared_ptr<HouseSceneReducer>);
    void HandleInput(const EventWithMouse &);
    void Update();
    void Draw(sf::RenderTarget &window);
};
