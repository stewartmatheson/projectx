#pragma once


#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Controller.h"
#include "EventWithMouse.h"
#include "HouseSceneReducer.h"
#include "HouseSceneState.h"
#include "Map.h"
#include "SpriteSheet.h"
#include "ViewLayer.h"
#include "AssetWatcher.h"
#include "ControllerScheme.h"

struct TimedController {
    sf::Clock timer;
    std::unique_ptr<Controller<HouseSceneReducer>> controller;
};

class HouseScene {
    HouseSceneState state;
    AssetWatcher asset_watcher;
    int tile_palette_offset;
    int toolbar_offset;
    std::vector<TimedController> timed_controllers;
    ViewLayer house_map_view_layer;
    ViewLayer tile_palette_view_layer;
    ViewLayer toolbar_view_layer;
    std::shared_ptr<std::unordered_map<EntityState, Animation>>
        player_animations;
    HouseSceneReducer reducer;
    void Init(int, int, std::shared_ptr<ControllerScheme>);
    void InitAnimations();
    void InitHouseMapView();
    void InitToolbarMap();
    void InitTools();
    void InitEntityMap();
    Map map;
  public:
    HouseScene(int, int, int, int, sf::IntRect, std::shared_ptr<ControllerScheme>);
    HouseScene(int, int, int, int, std::string, std::shared_ptr<ControllerScheme>);
    void HandleInput(const EventWithMouse &);
    void Update();
    void Draw(sf::RenderTarget &window);
};
