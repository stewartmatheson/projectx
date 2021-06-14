#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include "Controller.h"
#include "EventWithMouse.h"
#include "HouseSceneReducer.h"
#include "HouseSceneState.h"
#include "Map.h"
#include "ViewLayer.h"


class HouseScene {
    int offset;
    SpriteSheet tile_map;
    SpriteSheet entity_map;
    SpriteSheet player_sprite_sheet;
    HouseSceneState state;
    int tile_palette_offset;
    std::vector<std::unique_ptr<Controller<HouseSceneReducer>>> controllers;
    ViewLayer house_map_view_layer;
    ViewLayer tile_palette_view_layer;
    std::shared_ptr<std::unordered_map<EntityState, Animation>> player_animations;
    HouseSceneReducer reducer;
    void Init(int, int);
    Map map;

public:
    HouseScene(int, int, int, sf::IntRect);
    HouseScene(int, int, int, std::string);
    void HandleInput(const EventWithMouse&);
    void Update();
    void Draw(sf::RenderTarget& window);
};

