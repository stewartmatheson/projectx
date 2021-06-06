#include "Entity.h"

Entity::Entity(
    EntityType type, 
    float speed, 
    float acceleration, 
    float x, 
    float y
) : 
acceleration(acceleration), 
facing_left(true),
speed(speed), 
transform(sf::Vector2f(x, y)),
type(type),
state(EntityState::Idle) {}

void Entity::Update() {

    if (velocity.x != 0 || velocity.y != 0) {
        state = EntityState::Walking;
    }  else {
        state = EntityState::Idle;
    }

    if (facing_left && velocity.x > 0) {
        facing_left = false;
    }

    if (!facing_left && velocity.x < 0) {
        facing_left = true;
    }
}

const sf::Vector2f& Entity::GetTransform() const {
    return transform;
}

const int Entity::GetTileMapIndex() const {
    typedef std::underlying_type<EntityType>::type utype;
    return static_cast<utype>(type);
}

const int Entity::GetRotation() const {
    return 0;
}

const EntityType Entity::GetEntityType() const {
    return type;
}

const EntityState Entity::GetEntityState() const {
    return state;
}

