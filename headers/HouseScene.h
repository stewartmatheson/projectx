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

    SpriteSheet &tile_map;

    float current_rotation;

    sf::Vector2i last_mouse_position;

    bool panning;

    sf::View* house_view;

    sf::RenderTexture house_render_texture;

    House &house;
    
    Entity &player;

    bool editor_enabled;

    TilePaletteView tile_palette_view;

public:
    HouseScene(SpriteSheet &, int, int, House &, Entity &);
    ~HouseScene();
    void Draw(sf::RenderTarget &);
    void Update(const sf::Event &, const sf::Vector2i);
};


