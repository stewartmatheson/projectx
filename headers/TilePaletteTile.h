#include <SFML/Graphics.hpp>
#include "Entity.h"

enum TilePaletteType { PaletteTile, PaletteEntity };

struct TilePaletteTile {
    sf::Sprite icon; 
    TilePaletteType type;
    EntityType entity_type;
};
