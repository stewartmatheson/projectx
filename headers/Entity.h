#pragma once

#include <SFML/Graphics.hpp>

class Entity {
    sf::Vector2f transform;
    sf::Vector2f direction;

    // TODO : This should move out somewhere that can handle keyboards, control pads and other custom bindings
    sf::Vector2f controller;
    float speed;
    float acceleration;
public:
    Entity(float speed, float acceleration);
    sf::Vector2f getTransform();
    void Update(const sf::Event &);
    void Draw(sf::RenderTarget &);
};


