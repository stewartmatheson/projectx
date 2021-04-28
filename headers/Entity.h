#pragma once

#include <SFML/Graphics.hpp>

class Entity {
    sf::Vector2f transform;
    sf::Vector2f direction;
    float speed;
public:
    Entity(float speed);
    sf::Vector2f getTransform();
    void Update(const sf::Event &);
    void Draw(sf::RenderTarget &);
};


