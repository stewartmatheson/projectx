#pragma once

#include <SFML/Graphics.hpp>
#include "TilePaletteView.h"
#include "SpriteSheet.h"
#include "House.h"
#include "Entity.h"

/**
 * An editor contains all data required to add, remove and edit tiles on a given map
 */
class HouseScene {
    // The current mouse house grid pos
    sf::Vector2i* current_mouse_grid_position;

    float current_rotation;

    bool editor_enabled;

    House &house;

    sf::RenderTexture house_render_texture;

    sf::View* house_view;

    sf::Vector2i last_mouse_position;

    bool panning;
    
    Entity &player;

    SpriteSheet &tile_map;

    TilePaletteView tile_palette_view;

public:
    HouseScene(SpriteSheet &, int, int, House &, Entity &);
    ~HouseScene();
    void Draw(sf::RenderTarget &);
    void Update(const sf::Event &, const sf::Vector2i);
};


