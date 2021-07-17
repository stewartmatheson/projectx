#include "Entity.h"

Entity::Entity(EntityType type, float speed, float acceleration, float x,
               float y)
    : acceleration(acceleration), facing_left(true), speed(speed),
      transform(sf::Vector2f(x, y)), type(type), state(EntityState::Idle) {}

void Entity::Update() {}

const sf::Vector2f &Entity::GetTransform() const { return transform; }

const int Entity::GetTileMapIndex() const {
    typedef std::underlying_type<EntityType>::type utype;
    return static_cast<utype>(type);
}

const int Entity::GetRotation() const { return 0; }

const EntityType Entity::GetEntityType() const { return type; }

const EntityState Entity::GetEntityState() const { return state; }

const sf::Vector2f &Entity::GetVelocity() const { return velocity; }

void Entity::SetVelocity(sf::Vector2f new_velocity) { velocity = new_velocity; }

void Entity::SetTransform(sf::Vector2f new_transform) {
    transform = new_transform;
}

void Entity::SetPlayerState(EntityState new_player_state) {
    state = new_player_state;
}

const float Entity::GetSpeed() const { return speed; }

const float Entity::GetAcceleration() const { return acceleration; }
