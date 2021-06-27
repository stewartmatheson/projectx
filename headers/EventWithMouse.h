#pragma once

#include <SFML/Window.hpp>

struct EventWithMouse {
    const sf::Event &event;
    const sf::Vector2i &window_mouse_position;
};
