#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

#include "EventWithMouse.h"

struct ControllerSchemeState {
    sf::Vector2f direction;
    bool loot_action_pressed;
    bool attack_pressed;
};

class ControllerScheme {

  public:
    virtual std::optional<ControllerSchemeState>
    GetInput(const EventWithMouse &) const = 0;
};
