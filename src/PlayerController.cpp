#include "PlayerController.h"

PlayerController::PlayerController(
    std::weak_ptr<std::unordered_map<EntityState, Animation>> animations)
    : animations(animations) {}

void PlayerController::HandleInput(const EventWithMouse &event_with_mouse,
                                   HouseSceneReducer &state) {

    if (event_with_mouse.event.type == sf::Event::KeyPressed &&
        event_with_mouse.event.key.code == sf::Keyboard::Left) {
        current_input = sf::Vector2f(-1, 0);
    }

    if (event_with_mouse.event.type == sf::Event::KeyPressed &&
        event_with_mouse.event.key.code == sf::Keyboard::Right) {
        current_input = sf::Vector2f(1, 0);
    }

    if (event_with_mouse.event.type == sf::Event::KeyPressed &&
        event_with_mouse.event.key.code == sf::Keyboard::Up) {
        current_input = sf::Vector2f(0, -1);
    }

    if (event_with_mouse.event.type == sf::Event::KeyPressed &&
        event_with_mouse.event.key.code == sf::Keyboard::Down) {
        current_input = sf::Vector2f(0, 1);
    }

    if (event_with_mouse.event.type == sf::Event::KeyReleased) {
        current_input = sf::Vector2f(0, 0);
    }
}

void PlayerController::Update(HouseSceneReducer &reducer, sf::Time delta_time) {
    auto entities = reducer.GetState().entities;

    // TODO : There has to be a better way of doing this. It might get very slow
    // to have to search all entites all the time.
    auto found_player =
        std::find_if(entities.begin(), entities.end(), [](const auto &entity) {
            return entity.type == EntityType::PlayerEntity;
        });

    if (found_player == entities.end()) {
        return;
    }

    auto acceleration = sf::Vector2f(0, 0);
    auto const force =
        (delta_time.asMilliseconds() * found_player->acceleration) / 1000;

    acceleration +=
        sf::Vector2f(force * current_input.x, force * current_input.y);

    auto new_velocity = found_player->velocity + acceleration;
    // TODO : Note this is a damping const of 0.1. We most likley
    auto const new_damping =
        sf::Vector2f(-new_velocity.x, -new_velocity.y) * 0.1f;

    new_velocity += new_damping;
    reducer.SetEntityVelocity(new_velocity);

    auto rooms = reducer.GetState().rooms;
    // TODO : Remove Magic number
    auto sprite_size = reducer.GetState().scale * 16;

    auto room_the_player_is_in = std::find_if(rooms.begin(), rooms.end(), [found_player, sprite_size](const auto &room) { 
        return sf::FloatRect(
            room.left * sprite_size,
            room.top * sprite_size,
            room.width * sprite_size,
            room.height * sprite_size
        ).contains(found_player->transform);
    });

    if (room_the_player_is_in == rooms.end() || found_player->hitboxes.size() < 1) {
        reducer.SetEntityTransform(found_player->transform + new_velocity);
    } else {
        auto scaled_room =
            sf::IntRect(room_the_player_is_in->left * sprite_size,
                          room_the_player_is_in->top * sprite_size,
                          room_the_player_is_in->width * sprite_size,
                          room_the_player_is_in->height * sprite_size);

		reducer.SetEntityTransform(ClampToRoom(
			found_player->hitboxes[0], // TODO : Not sure what to do when we have more than one hitbox
			scaled_room,
			found_player->transform,
			found_player->transform + new_velocity
		));
    }

    if (new_velocity.x > 0.01f || new_velocity.x < -0.01f ||
        new_velocity.y > 0.01f || new_velocity.y < -0.01f) {
        reducer.SetPlayerState(EntityState::Walking);
    } else {
        reducer.SetPlayerState(EntityState::Idle);
    }

    if (!reducer.GetState().editor_state.editor_enabled) {
        reducer.SetHouseViewCenter(found_player->transform);
    }

    reducer.SetPlayerDirection(current_input);

    // TODO : This most likely won't work as different entities will move the
    // animations around before they are drawn
    if (auto shared_animations = animations.lock()) {
        auto state = reducer.GetState();
        auto found_player =
            std::find_if(state.entities.begin(), state.entities.end(),
                         [](const auto &entity) {
                             return entity.type == EntityType::PlayerEntity;
                         });

        if (found_player != state.entities.end()) {
            auto current_animation =
                shared_animations->find(found_player->state);
            
            current_animation->second.sprite.setPosition(
                found_player->transform);

            current_animation->second.sprite.setScale(
                4 * found_player->direction.x,
                current_animation->second.sprite.getScale().y);
        }
    }
}

void PlayerController::Reset() {
    std::cout << "PlayerController::Reset not implemented yet" << std::endl;
    // entity.SetVelocity(sf::Vector2f(0, 0));
}

sf::Vector2f PlayerController::ClampToRoom(
    sf::FloatRect player_hitbox, 
    sf::IntRect room, 
    sf::Vector2f original_position,
    sf::Vector2f new_position) {

    auto offset_hitbox = sf::FloatRect(new_position.x - player_hitbox.width / 2,
                                       new_position.y - player_hitbox.height / 2,
                                       player_hitbox.width,
                                       player_hitbox.height
    );

    // clamp left
    if (offset_hitbox.left < room.left) {
        new_position.x = original_position.x; 
    }

    //clamp right
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
