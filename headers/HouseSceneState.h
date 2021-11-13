#pragma once

#include "Entity.h"
#include "Item.h"
#include "TileLayer.h"
#include "TilePaletteTile.h"

enum class ToolType { Room };

typedef std::vector<sf::IntRect> Rooms;

struct Tool {
    ToolType type;
    int sprite_map_index;
};

struct HouseSceneEditorState {
    bool editor_enabled = false;
    bool panning = false;
    int selected_tile_index = 0;
    sf::IntRect editor_selection;
    int selected_tile_layer;
    int selected_tile_rotation = 0;
    sf::RectangleShape tile_palette_selection_rectangle;
    std::vector<TilePaletteTile> tile_palette_tiles;
    sf::Vector2i selected_editor_square;
    bool mouse_down = false;
    bool mouse_dragging = false;
    sf::Vector2f mouse_down_at;
    sf::Vector2f current_mouse_position;
    sf::IntRect map_selection;
    std::vector<Tool> tools;
};

struct MapState {
    int tile_pixel_count;
    Rooms rooms;
    sf::IntRect bounds = sf::IntRect(0,0,20,20);
    std::vector<Entity> entities;
    std::vector<TileLayer> tile_layers;
};

struct HouseSceneState {
    std::vector<Entity> entities;
    std::vector<Item> player_items;
    HouseSceneEditorState editor_state;
    MapState map;
};
