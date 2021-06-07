#include "Entity.h"

Entity::Entity(
    EntityType type, 
    float speed, 
    float acceleration, 
    float x, 
    float y,
    std::unordered_map<EntityState, Animation>& animations
) : 
acceleration(acceleration), 
facing_left(true),
speed(speed), 
transform(sf::Vector2f(x, y)),
type(type),
state(EntityState::Idle),
animations(animations) {}

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
    
    auto current_animation = animations.find(GetEntityState());
    if (facing_left) {
        current_animation->second.sprite.setScale(
            -4,
            current_animation->second.sprite.getScale().y
        );
    } else {
        current_animation->second.sprite.setScale(
            4,
            current_animation->second.sprite.getScale().y
        );
    } 
    current_animation->second.sprite.setPosition(GetTransform());
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

const sf::Vector2f& Entity::GetVelocity() const {
    return velocity;
}

void Entity::SetVelocity(sf::Vector2f new_velocity) {
    velocity = new_velocity;
}

void Entity::SetTransform(sf::Vector2f new_transform) {
    transform = new_transform;
}

const float Entity::GetSpeed() const {
    return speed;
}

const float Entity::GetAcceleration() const {
    return acceleration;
}
