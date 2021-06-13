#pragma once

#include <SFML/Graphics.hpp>
#include "EventWithMouse.h"

template <typename T>
class Controller {
public:
    virtual ~Controller() = default;
    virtual void Update(T&) = 0;
    virtual void HandleInput(EventWithMouse, T&) = 0;
};

