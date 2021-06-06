#pragma once

#include <SFML/Graphics.hpp>
#include "View.h"
#include "HouseSceneState.h"

class TilePaletteView : public View<HouseSceneState> {
    sf::RenderTexture& tile_palette_render_texture;
public:
    TilePaletteView(SpriteSheet&, SpriteSheet&, sf::RenderTexture&, int);
    ~TilePaletteView();
    void Draw(sf::RenderTarget&, const HouseSceneState&) const;
};
