#pragma once

#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

enum class EntityType { GhostEntity = 0, DoorEntity = 1, PlayerEntity = 2 };

enum class EntityState { Idle, Throwing, Walking, Attacking, Dying };

class Entity {
    float acceleration;
    sf::Vector2f direction;
    bool facing_left;
    float speed;
    sf::Vector2f transform;
    sf::Vector2f velocity;
    EntityType type;
    EntityState state;

  public:
    Entity(EntityType, float, float, float, float);
    void Update();

    const sf::Vector2f &GetTransform() const;
    const sf::Vector2f &GetVelocity() const;
    const float GetAcceleration() const;
    const int GetTileMapIndex() const;
    const int GetRotation() const;
    const EntityType GetEntityType() const;
    const EntityState GetEntityState() const;
    const bool GetFacingLeft() const;
    const float GetSpeed() const;

    void SetVelocity(sf::Vector2f);
    void SetTransform(sf::Vector2f);
    void SetPlayerState(EntityState);
};
