#pragma once

#include "Entity.h"

class EntityFactory {
  public:
    static Entity Player(sf::Vector2f);
    static Entity Ghost(sf::Vector2f);
};
