#pragma once

#include "View.h"
#include "HouseSceneState.h"

class GridSelectionView : public View<HouseSceneState> {
    int sprite_size;
public:
    GridSelectionView(int sprite_size);
    void Draw(sf::RenderTarget&, const HouseSceneState&) const;
};
