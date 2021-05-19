#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include "TilePaletteTile.h"


class TilePaletteView {
    
    // The background shape for the tile toolbar editor
    sf::RectangleShape* background;	

    sf::RenderTexture icon_sprite_render_texture;

    // The offset defines gaps between the tiles on the left hand tile editor
    int offset;
    
    // The currently selected tile index. This is the index for the tiles vector
    int selected_tile_index;

    // The blue rect around the selected tile in the tile palette
    sf::RectangleShape* selection_rectangle;	

    SpriteSheet &tile_map;
    
    sf::RenderTexture* tile_palette_render_texture;

    // The view for the current tile palette that appears on the left side of the window
    sf::View* tile_palette_view;

    // A list of vector of spirte tiles for rendering in the sidebar of the editor
    // std::vector<sf::Sprite>* tiles;
    std::vector<TilePaletteTile> tiles;

    sf::Sprite CreateIconSprite(int, sf::Color, int);

public:
    TilePaletteView(SpriteSheet&, int);
    ~TilePaletteView();
    sf::RectangleShape* GetBackground();
    void Draw(sf::RenderTarget &);
    void Update(const sf::Event &, const sf::Vector2i);
    int GetSelectedTileIndex();
    sf::Sprite& GetSelectedTileSprite();

};
