#include "Entity.h"
#include <SFML/Graphics.hpp>

enum class TilePaletteType { PaletteTile, PaletteEntity };

struct TilePaletteTile {
    sf::Sprite icon;
    TilePaletteType type;
    EntityType entity_type;
};
