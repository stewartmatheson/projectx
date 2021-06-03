#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include "TilePaletteTile.h"


class TilePaletteView {
    

    // The view for the current tile palette that appears on the left side of the window


public:
    TilePaletteView(SpriteSheet&, SpriteSheet&, int);
    ~TilePaletteView();
    void Draw(sf::RenderTarget &);
};
