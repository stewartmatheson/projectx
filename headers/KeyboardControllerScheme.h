#pragma once

#include "ControllerScheme.h"

class KeyboardControllerScheme : public ControllerScheme {
  public:
	sf::Vector2f GetInput(const EventWithMouse&) const;
};
