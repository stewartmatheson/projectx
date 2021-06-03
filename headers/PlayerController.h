
#pragma once

#include "Controller.h"

class PlayerController : Controller {
public:
    void Update();
    void HandleInput(sf::Event& event);
};


