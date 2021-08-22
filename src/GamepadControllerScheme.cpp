#include "GamepadControllerScheme.h"
#include <iostream>
#include <SFML/Window/Joystick.hpp>

sf::Vector2f GamepadControllerScheme::GetInput(const EventWithMouse &) const {
    float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100;
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100;
    return sf::Vector2f(x, y);
}
