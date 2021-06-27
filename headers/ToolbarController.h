#pragma once

#include "Controller.h"
#include "HouseSceneReducer.h"

class ToolbarController : public Controller<HouseSceneReducer> {
  public:
    void Update(HouseSceneReducer &);
    void HandleInput(const EventWithMouse &, HouseSceneReducer &);
};
