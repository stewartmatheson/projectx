
#pragma once

#include "Controller.h"
#include "HouseSceneReducer.h"
#include "EventWithMouse.h"

class PlayerController : public Controller<HouseSceneReducer> {
    sf::Vector2f current_input;
public:
    PlayerController();
    void Update(HouseSceneReducer&);
    void HandleInput(EventWithMouse, HouseSceneReducer&);
    void Reset();
};


