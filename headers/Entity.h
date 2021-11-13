#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <list>

enum class EntityType { GhostEntity = 0, DoorEntity = 1, PlayerEntity = 2 };
enum class EntityState { Idle, Throwing, Walking, Attacking, Dying };
enum class AIState { None, Attacking, Patrolling };

struct Entity;

struct EntityAI {
    AIState state = AIState::None;
    std::list<sf::Vector2f> waypoints;
    int waypoint_index = 0;
    std::weak_ptr<Entity> target;
};

struct Entity {
    EntityType type;
    float speed;
    float acceleration;
    sf::Vector2f transform;
    sf::Vector2f direction = sf::Vector2f(1, 1);
    sf::Vector2f velocity;
    EntityState state;
    int rotation;
    std::vector<sf::FloatRect> hitboxes;
    double facing;
    EntityAI ai;
};

