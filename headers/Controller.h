#pragma once

#include "EventWithMouse.h"
#include <SFML/Graphics.hpp>

template <typename T> class Controller {
  public:
    virtual ~Controller() = default;
    virtual void Update(T &, sf::Time) = 0;
    virtual void HandleInput(const EventWithMouse &, T &) = 0;
};
