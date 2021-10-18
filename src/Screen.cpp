#include "Screen.h"

Screen::Screen(sf::IntRect window_size, int scale, int toolbar_icon_padding,
               int toolbar_icon_size, int tile_palette_offset,
               int toolbar_offset, const int tile_map_sprite_size)
    : window_size(window_size), scale(scale),
      toolbar_icon_padding(toolbar_icon_padding),
      toolbar_icon_size(toolbar_icon_size),
      tile_palette_offset(tile_palette_offset),
      tile_map_sprite_size(tile_map_sprite_size),
      toolbar_offset(toolbar_offset) {}

const sf::IntRect Screen::GetButtonArea() const {
    return sf::IntRect(GetTilePaletteArea().width + toolbar_icon_padding,
                       toolbar_icon_padding, toolbar_icon_size * scale,
                       toolbar_icon_size * scale);
}

const sf::IntRect Screen::GetWindowSize() const { return window_size; }

const sf::IntRect Screen::GetTilePaletteArea() const {
    return sf::IntRect(0, 0,
                       tile_palette_offset * 2 + (tile_map_sprite_size * scale),
                       window_size.height);
}

const sf::IntRect Screen::GetToolbarArea() const {
    return sf::IntRect(tile_palette_offset * 2 + (tile_map_sprite_size * scale),
                       0, window_size.width, 60);
}

const int Screen::GetToolbarOffset() const { return toolbar_offset; }
const int Screen::GetTilePaletteOffset() const { return tile_palette_offset; }

const int Screen::GetScale() const { return scale; }

const int Screen::GetToolbarIconPadding() const { return toolbar_icon_padding; }
