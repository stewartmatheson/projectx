#pragma once
#include "ControllerScheme.h"
#include "EventWithMouse.h"

class GamepadControllerScheme : public ControllerScheme {
  public:
	 sf::Vector2f GetInput(const EventWithMouse&) const;
};
