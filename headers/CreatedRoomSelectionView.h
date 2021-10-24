#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "HouseScene.h"
#include "View.h"

class CreatedRoomSelectionView : public View<HouseSceneState> {
  public:
    void Draw(sf::RenderTarget &, const HouseSceneState &) const;
    void Update();
};
