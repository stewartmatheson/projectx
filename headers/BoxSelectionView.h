
#pragma once

#include "View.h"
#include "HouseScene.h"

class BoxSelectionView : public View<HouseSceneState> {
public: 
    void Draw(sf::RenderTarget&, const HouseSceneState&) const;
};
