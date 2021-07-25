#pragma once

#include "HouseSceneState.h"
#include "View.h"

class TileBackgroundView : public View<HouseSceneState> {
    const SpriteSheet &tile_map;

  public:
    TileBackgroundView(const SpriteSheet &);
    void Draw(sf::RenderTarget &, const HouseSceneState &) const;
    void Update();
};
