#pragma once
#include <SFML/Graphics.hpp>

class Screen {
    /*
    sf::IntRect window_size;
    int scale;
    int toolbar_icon_padding;
    int toolbar_icon_size;
    int tile_palette_offset;
    int toolbar_offset;
    const int tile_map_sprite_size;
    */

  public:
    //Screen(sf::IntRect, int, int, int, int, int, const int);
    static const sf::IntRect GetButtonArea();
    static const sf::IntRect GetWindowSize();
    static const sf::IntRect GetTilePaletteArea();
    static const sf::IntRect GetToolbarArea();
    static int GetToolbarOffset();
    static int GetTilePaletteOffset();
    static int GetScale();
    static int GetToolbarIconPadding();
};
