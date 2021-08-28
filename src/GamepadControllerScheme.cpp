#include "GamepadControllerScheme.h"
#include <iostream>
#include <algorithm>
#include <SFML/Window/Joystick.hpp>

sf::Vector2f GamepadControllerScheme::GetInput(const EventWithMouse &) const {
    float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100;
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100;
    float threshhold = .08f;

    if ((x < threshhold && x > 0) || (x > threshhold * -1 && x < 0)) {
        x = 0;
    }

    if ((y < threshhold && y > 0) || (y > threshhold * -1 && y < 0)) {
        y = 0;
    }

    std::cout << x << ", " << y << std::endl;
    return sf::Vector2f(x, y);
}
