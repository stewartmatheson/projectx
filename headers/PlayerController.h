
#pragma once

#include "Controller.h"
#include "HouseSceneReducer.h"
#include "EventWithMouse.h"

class PlayerController : public Controller<HouseSceneReducer> {
    Entity& entity;
    sf::Vector2f current_input;
public:
    PlayerController(Entity&);
    void Update(HouseSceneReducer&);
    void HandleInput(EventWithMouse, HouseSceneReducer&);
    void Reset();
};


