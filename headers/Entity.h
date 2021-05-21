#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Animation.h"

enum EntityType { PlayerEntity, GhostEntity, DoorEntity };

class Entity {
    float acceleration;
    std::unordered_map<std::string, Animation> animations;
    // TODO : This should move out somewhere that can handle keyboards, control pads and other custom bindings
    sf::Vector2f controller;
    sf::Vector2f direction;
    bool facing_left;
    float speed;
    sf::Vector2f transform;
    EntityType type;

public:
    Entity(EntityType, float, float);
    Entity(EntityType, float, float, std::unordered_map<std::string, Animation>&);
    sf::Vector2f &getTransform();
    void Update(const sf::Event &);
    void Draw(sf::RenderTarget &);
    void Reset();
};


