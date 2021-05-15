#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Animation.h"

enum EntityType { PlayerEntity, GhostEntity, DoorEntity };

class Entity {
    sf::Vector2f transform;
    sf::Vector2f direction;

    // TODO : This should move out somewhere that can handle keyboards, control pads and other custom bindings
    sf::Vector2f controller;
    float speed;
    float acceleration;
    bool facing_left;
    std::unordered_map<std::string, Animation> animations;
    EntityType type;

public:
    Entity(EntityType, float, float);
    Entity(EntityType, float, float, std::unordered_map<std::string, Animation>&);
    sf::Vector2f getTransform();
    void Update(const sf::Event &);
    void Draw(sf::RenderTarget &);
    void Reset();
};


