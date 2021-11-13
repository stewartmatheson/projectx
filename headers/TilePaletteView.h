#pragma once

#include "HouseSceneState.h"
#include "View.h"
#include "Screen.h"
#include <SFML/Graphics.hpp>

class TilePaletteView : public View<HouseSceneState> {
    sf::RenderTexture tile_palette_render_texture;
  public:
    TilePaletteView(int, int);
    void Draw(sf::RenderTarget &, const HouseSceneState &) const;
    void Update();
};
