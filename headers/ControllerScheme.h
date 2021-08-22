#pragma once

#include <SFML/Graphics.hpp>
#include "EventWithMouse.h"

class ControllerScheme {

public:
	virtual sf::Vector2f GetInput(const EventWithMouse&) const = 0;
};
