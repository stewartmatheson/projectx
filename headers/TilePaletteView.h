#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include "TilePaletteTile.h"


class TilePaletteView {
    
    // The background shape for the tile toolbar editor
    sf::RectangleShape background;


    // The offset defines gaps between the tiles on the left hand tile editor
    int offset;
    
    // The currently selected tile index. This is the index for the tiles vector
    int selected_tile_index;

    // The blue rect around the selected tile in the tile palette
    sf::RectangleShape selection_rectangle;

    SpriteSheet &tile_map;

    SpriteSheet &entity_map;
    
    sf::RenderTexture tile_palette_render_texture;

    // The view for the current tile palette that appears on the left side of the window
    sf::View tile_palette_view;

    std::vector<TilePaletteTile> tiles;

public:
    TilePaletteView(SpriteSheet&, SpriteSheet&, int);
    ~TilePaletteView();
    const sf::RectangleShape &GetBackground() const;
    void Draw(sf::RenderTarget &);
    void Update(const sf::Event &, const sf::Vector2i);
    int GetSelectedTileIndex() const;
    const TilePaletteTile& GetSelectedTile() const;
};
