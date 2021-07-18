#pragma once

#include "Controller.h"
#include "EventWithMouse.h"
#include "HouseSceneReducer.h"
#include "HouseSceneState.h"
#include "Map.h"
#include "SpriteSheet.h"
#include "ViewLayer.h"
#include <SFML/Graphics.hpp>

struct TimedController {
    sf::Clock timer;
    std::unique_ptr<Controller<HouseSceneReducer>> controller;
};

class HouseScene {
    HouseSceneState state;
    SpriteSheet tile_map;
    SpriteSheet entity_map;
    SpriteSheet player_sprite_sheet;
    SpriteSheet toolbar_sprite_sheet;
    int tile_palette_offset;
    int toolbar_offset;
    std::vector<TimedController> timed_controllers;
    ViewLayer house_map_view_layer;
    ViewLayer tile_palette_view_layer;
    ViewLayer toolbar_view_layer;
    std::shared_ptr<std::unordered_map<EntityState, Animation>>
        player_animations;
    HouseSceneReducer reducer;
    void Init(int, int);
    void InitAnimations();
    void InitHouseMapView();
    void InitToolbarMap();
    void InitTools();
    void InitEntityMap();
    Map map;

  public:
    HouseScene(int, int, int, int, sf::IntRect);
    HouseScene(int, int, int, int, std::string);
    void HandleInput(const EventWithMouse &);
    void Update();
    void Draw(sf::RenderTarget &window);
};
