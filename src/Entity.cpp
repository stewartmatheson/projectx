#include "Entity.h"

Entity::Entity(EntityType type, float speed, float acceleration, float x, float y) : 
    acceleration(acceleration), 
    animations(),
    facing_left(true),
    speed(speed), 
    transform(sf::Vector2f(x, y)),
    type(type) {}

Entity::Entity(
    EntityType type,
    float speed, 
    float acceleration,
    std::unordered_map<std::string, Animation>& animations
) : acceleration(acceleration), animations(animations), speed(speed), type(type) {}

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

    std::string current_animation_key = "idle";

    if (controller.x != 0 || controller.y != 0) {
        current_animation_key = "walk";
    } 

    auto current_animation = animations.find(current_animation_key);

    if (facing_left && controller.x > 0) {
        facing_left = false;
    }

    if (!facing_left && controller.x < 0) {
        facing_left = true;
    }

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


const sf::Vector2f &Entity::getTransform() const {
    return transform;
}

void Entity::Reset() {
    controller.x = 0;
    controller.y = 0;
}

sf::Vector2f Entity::GetTransform() const {
    return transform;
}

int Entity::GetTileMapIndex() const {
    /*
    if (type == DoorEntity) {
        return 1;
    } else if (type == PlayerEntity) {
        return 0;
    } else {
        std::cout << "Unknown Entity Type : " << type << std::endl;
        exit(1);
    }
    */
    return type;
}

int Entity::GetRotation() const {
    return 0;
}
