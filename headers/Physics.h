#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Physics {

    static sf::Vector2f ClampToRoom(sf::FloatRect, sf::FloatRect, sf::Vector2f,
                                    sf::Vector2f);

  public:
    static sf::Vector2f StepPosition(Entity &, sf::Vector2f, sf::Time,
                                     std::vector<sf::IntRect>);
};