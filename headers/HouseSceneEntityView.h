#pragma once

#include "HouseSceneState.h"
#include "View.h"

class HouseSceneEntityView : public View<HouseSceneState> {
    const SpriteSheet& tile_map;
public:
    HouseSceneEntityView(const SpriteSheet& tile_map);
    void Draw(sf::RenderTarget&, const HouseSceneState&) const;
};
