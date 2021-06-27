#pragma once

#include "HouseScene.h"
#include "View.h"

class GridView : public View<HouseSceneState> {
    int size;

  public:
    GridView(int);
    void Draw(sf::RenderTarget &, const HouseSceneState &) const;
};
