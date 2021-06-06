#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include "View.h"
#include "Controller.h"
#include "EventWithMouse.h"
#include "HouseSceneReducer.h"
#include "HouseSceneState.h"
#include "Map.h"

class HouseScene {
    SpriteSheet tile_map;
    SpriteSheet entity_map;
    SpriteSheet player_sprite_sheet;
    HouseSceneState state;
    sf::RenderTexture scene_render_target;
    sf::RenderTexture tile_palette_render_texture;
    int tile_palette_offset;
    std::vector<std::unique_ptr<Controller<HouseSceneReducer>>> controllers;
    std::vector<std::unique_ptr<View<HouseSceneState>>> views;
    HouseSceneReducer reducer;
    void Init(int, int);
    Map map;

public:
    HouseScene(int, int, sf::IntRect);
    HouseScene(int, int, std::string);
    void HandleInput(EventWithMouse);
    void Update();
    void Draw(sf::RenderTarget& window);
};

