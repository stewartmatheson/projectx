#pragma once

#include <SFML/Window.hpp>

struct EventWithMouse {
    sf::Event& event;
    sf::Vector2i window_mouse_position;
};

