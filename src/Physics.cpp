#include "Physics.h"
#include "Map.h"

sf::Vector2f Physics::StepPosition(Entity &entity, sf::Vector2f position,
                                   sf::Time delta_time,
                                   std::vector<sf::IntRect> rooms) {

    auto acceleration = sf::Vector2f(0, 0);
    auto const force =
        (delta_time.asMilliseconds() * entity.acceleration) / 1000;

    // TODO : I think we might have to normalise here
    auto target_vector = position;

    acceleration +=
        sf::Vector2f(force * target_vector.x, force * target_vector.y);
    auto velocity = entity.velocity + acceleration;
    auto const damping = sf::Vector2f(-velocity.x, -velocity.y) * 0.1f;
    velocity += damping;

    entity.velocity = velocity;
    auto room =
        std::find_if(rooms.begin(), rooms.end(), [entity](const auto &room) {
            auto sprite_size = Screen::GetScale() * Map::GetSpriteSize();
            return sf::FloatRect(
                       room.left * sprite_size, room.top * sprite_size,
                       room.width * sprite_size, room.height * sprite_size)
                .contains(entity.transform);
        });

    auto entity_free_roam = room == rooms.end() || entity.hitboxes.size() < 1;

    auto sprite_size = Screen::GetScale() * Map::GetSpriteSize();
    auto scaled_room =
        sf::FloatRect(room->left * sprite_size, room->top * sprite_size,
                      room->width * sprite_size, room->height * sprite_size);

    if (entity_free_roam) {
        return entity.transform + velocity;
    } else {
        return ClampToRoom(entity.hitboxes[0], scaled_room, entity.transform,
                           entity.transform + velocity);
    }
}

sf::Vector2f Physics::ClampToRoom(sf::FloatRect player_hitbox,
                                  sf::FloatRect room,
                                  sf::Vector2f original_position,
                                  sf::Vector2f new_position) {

    auto offset_hitbox =
        sf::FloatRect(new_position.x - player_hitbox.width / 2,
                      new_position.y - player_hitbox.height / 2,
                      player_hitbox.width, player_hitbox.height);

    // clamp left
    if (offset_hitbox.left < room.left) {
        new_position.x = original_position.x;
    }

    // clamp right
    if (offset_hitbox.left + player_hitbox.width > room.left + room.width) {
        new_position.x = original_position.x;
    }

    // clamp top
    if (offset_hitbox.top < room.top) {
        new_position.y = original_position.y;
    }

    // clamp bottom
    if (offset_hitbox.top + offset_hitbox.height > room.top + room.height) {
        new_position.y = original_position.y;
    }

    return new_position;
}
