#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include "House.h"
#include "Entity.h"

/**
 * An editor contains all data required to add, remove and edit tiles on a given map
 */
class HouseScene {
    // The blue rect around the selected tile in the tile palette
    sf::RectangleShape* selection_rectangle;	

    // The current mouse house grid pos
    sf::Vector2i* current_mouse_grid_position;

    // The background shape for the tile toolbar editor
    sf::RectangleShape* background;	

    // A list of vector of spirte tiles for rendering in the sidebar of the editor
    std::vector<sf::Sprite>* tiles;

    // The offset defines gaps between the tiles on the left hand tile editor
    int offset;

    SpriteSheet &tile_map;

    // The currently selected tile index. This is the index for the tiles vector
    int selected_tile_index;

    // The view for the current tile palette that appears on the left side of the window
    sf::View* tile_palette_view;

    sf::RenderTexture* tile_palette_render_texture;

    float current_rotation;

    sf::Vector2i last_mouse_position;

    bool panning;

    sf::View* house_view;

    sf::RenderTexture* house_render_texture;

    House &house;
    
    Entity &player;

    bool editor_enabled;

public:
    HouseScene(SpriteSheet &, int, int, House &, Entity &);
    ~HouseScene();
    void Draw(sf::RenderTarget &);
    void Update(const sf::Event &, const sf::Vector2i);
};


