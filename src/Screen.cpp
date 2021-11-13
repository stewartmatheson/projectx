#include "Screen.h"
#include "Map.h"
#include "ScreenValues.h"

const sf::IntRect Screen::GetButtonArea() {
    return sf::IntRect(GetTilePaletteArea().width + toolbar_icon_padding,
                       toolbar_icon_padding, toolbar_icon_size * scale,
                       toolbar_icon_size * scale);
}

const sf::IntRect Screen::GetWindowSize() { 
    return sf::IntRect(0, 0, window_width, window_height); 
}

const sf::IntRect Screen::GetTilePaletteArea() {
    auto window_size = GetWindowSize();
    return sf::IntRect(0, 0,
                       tile_palette_offset * 2 + (Map::GetSpriteSize() * scale),
                       window_size.height);
}

const sf::IntRect Screen::GetToolbarArea() {
    auto window_size = GetWindowSize();
    return sf::IntRect(tile_palette_offset * 2 + (Map::GetSpriteSize() * scale),
                       0, window_size.width, 60);
}

int Screen::GetToolbarOffset() { return toolbar_offset; }
int Screen::GetTilePaletteOffset() { return tile_palette_offset; }

int Screen::GetScale() { return scale; }

int Screen::GetToolbarIconPadding() { return toolbar_icon_padding; }
