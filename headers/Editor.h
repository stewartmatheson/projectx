#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Room.h"

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

    sf::Vector2i last_mouse_position;

    bool panning;

    sf::View* room_view;

    sf::RenderTexture* room_render_texture;

    Editor(TileMap &, int, int);
    ~Editor();

    void DrawEditor(sf::RenderTarget &, Room &);

    void UpdateEditor(const sf::Event &, Room&, const sf::Vector2i);
};

void WriteRoomToFile(Room &, std::string);
