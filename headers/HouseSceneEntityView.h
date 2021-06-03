#pragma once

#include "HouseScene.h"

class HouseSceneEntityView : public View<HouseSceneState> {
    SpriteSheet& entity_map;
public:
    HouseSceneEntityView();
    void Draw(sf::RenderTarget&, const HouseSceneState&);
};
