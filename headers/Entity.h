#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Entity {
    sf::Vector2f transform;
    sf::Vector2f direction;

    // TODO : This should move out somewhere that can handle keyboards, control pads and other custom bindings
    sf::Vector2f controller;
    float speed;
    float acceleration;
    std::unordered_map<std::string, Animation> animations;

public:
    Entity(float speed, float acceleration);
    Entity(float speed, float acceleration, std::unordered_map<std::string, Animation>&);
    sf::Vector2f getTransform();
    void Update(const sf::Event &);
    void Draw(sf::RenderTarget &);
};


