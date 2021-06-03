#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include "Entity.h"
#include "Map.h"
#include "View.h"
#include "Controller.h"
#include "EventWithMouse.h"
#include "TilePaletteTile.h"

struct HouseSceneState {
    std::vector<TileLayer> tile_layers;
    std::vector<Entity<HouseSceneState>> entities;
    sf::IntRect map_bounds;
    std::vector<TilePaletteTile> tile_palette_tiles;
    sf::View tile_palette_view;
    sf::View house_view;
    bool editor_enabled;
    bool panning;
    int selected_tile_index;
    sf::Vector2i tile_palette_bounds;
    int selected_tile_layer;
    int selected_tile_rotation;
    sf::RectangleShape tile_palette_background;
    sf::RectangleShape tile_palette_selection_rectangle;

};

class HouseScene {
    SpriteSheet tile_map;
    SpriteSheet entity_map;
    SpriteSheet player_sprite_sheet;
    std::unordered_map<EntityMode, Animation> player_animations;
    HouseSceneState state;
    sf::RenderTexture scene_render_target;
    sf::RenderTexture tile_palette_render_texture;
    int tile_palette_offset;
    std::vector<Controller<HouseSceneState>&> controllers;
    std::vector<View<HouseSceneState>&> views;
    const HouseSceneReducer reducer;

public:
    HouseScene(int, int);
    void HandleInput(EventWithMouse);
    void Update();
    void Draw(sf::RenderTarget& window);
};

