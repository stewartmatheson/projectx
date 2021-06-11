#pragma once

#include "Entity.h"
#include "TilePaletteTile.h"
#include "TileLayer.h"

struct HouseSceneEditorState {
    bool editor_enabled = false;
    bool panning;
    int selected_tile_index = 0;
    sf::IntRect tile_palette_bounds;
    int selected_tile_layer;
    int selected_tile_rotation;
    int tile_palette_background_total_height;
    sf::RectangleShape tile_palette_background;
    sf::RectangleShape tile_palette_selection_rectangle;
    sf::View tile_palette_view;
    std::vector<TilePaletteTile> tile_palette_tiles;
};

struct HouseSceneState {
    std::vector<Entity> entities;
    std::vector<TileLayer> tile_layers;
    sf::IntRect map_bounds;
    sf::View house_view;
    HouseSceneEditorState editor_state;
};
