#pragma once

#include "HouseScene.h"

class TileBackgroundView : public View<HouseSceneState> {
    SpriteSheet& tile_map;
public:
    TileBackgroundView(SpriteSheet&);
    void Draw(sf::RenderTarget&, const HouseSceneState&) const;
};
