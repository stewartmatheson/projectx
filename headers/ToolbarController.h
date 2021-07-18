#pragma once

#include "Controller.h"
#include "HouseSceneReducer.h"

class ToolbarController : public Controller<HouseSceneReducer> {
  public:
    void Update(HouseSceneReducer &, sf::Time);
    void HandleInput(const EventWithMouse &, HouseSceneReducer &);
};
