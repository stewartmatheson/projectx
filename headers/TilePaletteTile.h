#include <SFML/Graphics.hpp>

enum TilePaletteType { PaletteTile, PaletteEntity };

struct TilePaletteTile {
    sf::Sprite icon;
    TilePaletteType type;
};
