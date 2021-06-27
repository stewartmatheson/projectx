
#pragma once

#include "Controller.h"
#include "EventWithMouse.h"
#include "HouseSceneReducer.h"

class PlayerController : public Controller<HouseSceneReducer> {
    sf::Vector2f current_input;

  public:
    PlayerController();
    void Update(HouseSceneReducer &);
    void HandleInput(const EventWithMouse &, HouseSceneReducer &);
    void Reset();
};
