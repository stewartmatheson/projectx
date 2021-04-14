#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"

/**
 * An editor contains all data required to add, remove and edit tiles on a given map
 */
struct Editor {
    // The blue rect around the selected tile in the tile palette
    sf::RectangleShape* selection_rectangle;	

    // The current mouse room grid pos
    sf::Vector2i* current_mouse_grid_position;

    // The background shape for the tile toolbar editor
    sf::RectangleShape* background;	

    // A list of vector of spirte tiles for rendering in the sidebar of the editor
    std::vector<sf::Sprite>* tiles;

    // The offset defines gaps between the tiles on the left hand tile editor
    int offset;

    TileMap* tile_map;

    // The currently selected tile index. This is the index for the tiles vector
    int selected_tile_index;

    // The view for the current tile palette that appears on the left side of the window
    sf::View* tile_palette_view;

    sf::RenderTexture* tile_palette_render_texture;

    float current_rotation;

};


Editor *CreateEditor(TileMap &, int, int);

void DestructEditor(Editor &);

void DrawEditor(sf::RenderTarget &, Editor &, const int, const int);

typedef struct {
    enum Type { Save, PlaceTile, None };
    Type type;
    union {
        Tile tile;
    };
} EditorUpdateResult;

EditorUpdateResult UpdateEditor(Editor &, const sf::Event &);

