#pragma once

#include <SFML/Graphics.hpp>
#include "TilePaletteView.h"
#include "SpriteSheet.h"
#include "Map.h"
#include "Entity.h"

/**
 * An editor contains all data required to add, remove and edit tiles on a given map
 */
class HouseScene {
    sf::Vector2i current_mouse_grid_position;
    float current_rotation;
    bool editor_enabled;
    Map &map;
    sf::RenderTexture house_render_texture;
    sf::View house_view;
    sf::Vector2i last_mouse_position;
    bool panning;
    Entity &player;
    SpriteSheet &tile_map;
    SpriteSheet &entity_map;
    TilePaletteView tile_palette_view;
    int current_selected_tile_layer;

public:
    HouseScene(SpriteSheet&, SpriteSheet&, int, int, Map &, Entity &);
    ~HouseScene();
    void Draw(sf::RenderTarget &);
    void Update(const sf::Event &, const sf::Vector2i);
};


