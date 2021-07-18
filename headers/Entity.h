#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

enum class EntityType { GhostEntity = 0, DoorEntity = 1, PlayerEntity = 2 };

enum class EntityState { Idle, Throwing, Walking, Attacking, Dying };

struct Entity {
    EntityType type;
    float speed;
    float acceleration;
    sf::Vector2f transform;
    sf::Vector2f direction;
    bool facing_left;
    sf::Vector2f velocity;
    EntityState state;
    int rotation;
};
