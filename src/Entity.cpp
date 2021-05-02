#include "Entity.h"

Entity::Entity(float speed, float acceleration) : 
    speed(speed), 
    acceleration(acceleration), 
    animations() {}

Entity::Entity(
    float speed, 
    float acceleration,
    std::unordered_map<std::string, Animation>& animations
) : speed(speed), acceleration(acceleration), animations(animations) {}

void Entity::Update(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
        controller = sf::Vector2f(-1, 0);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
        controller = sf::Vector2f(1, 0);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
        controller = sf::Vector2f(0, -1);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
        controller = sf::Vector2f(0 , 1);
    }

    if (event.type == sf::Event::KeyReleased) {
        controller = sf::Vector2f(0 , 0);
    }

}

void Entity::Draw(sf::RenderTarget &target) {
    direction.x = ((controller.x * speed) - direction.x) * acceleration;
    direction.y = ((controller.y * speed) - direction.y) * acceleration;
    transform = transform + direction;

    auto current_animation = animations.find("idle");
    if(current_animation != animations.end()) {
        current_animation->second.Update();
        current_animation->second.sprite.setPosition(transform);
        target.draw(current_animation->second.sprite);
    } else {
        // TODO : We might not want to do this each draw call.
        sf::RectangleShape no_sprite(sf::Vector2f(50,80));
        no_sprite.setPosition(transform);
        target.draw(no_sprite);
    }
}

sf::Vector2f Entity::getTransform() {
    return transform;
}
