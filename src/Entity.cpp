#include "Entity.h"

Entity::Entity(float speed) : speed(speed) {}

void Entity::Update(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
        direction = sf::Vector2f(-1, 0);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
        direction = sf::Vector2f(1, 0);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
        direction = sf::Vector2f(0, -1);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
        direction = sf::Vector2f(0 , 1);
    }

    if (event.type == sf::Event::KeyReleased) {
        direction = sf::Vector2f(0 , 0);
    }

}

void Entity::Draw(sf::RenderTarget &target) {
    transform = transform + sf::Vector2f(direction.x * speed, direction.y * speed);

    // TODO : We might not want to do this each draw call.
    sf::RectangleShape no_sprite(sf::Vector2f(50,80));
    no_sprite.setPosition(transform);
    target.draw(no_sprite);
}

sf::Vector2f Entity::getTransform() {
    return transform;
}
