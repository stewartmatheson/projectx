#include "PlayerController.h"
#include <cmath>

PlayerController::PlayerController(
    std::shared_ptr<std::unordered_map<EntityState, Animation>> animations,
    std::shared_ptr<ControllerScheme> controller_scheme,
    ViewLayer &house_view)
    : animations(animations), controller_scheme(controller_scheme),
      house_view(house_view) {}

void PlayerController::HandleInput(const EventWithMouse &event_with_mouse,
                                   HouseSceneReducer &) {
    current_input = controller_scheme->GetInput(event_with_mouse);
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
    std::cout << found_player->transform.x << " " << found_player->transform.y
              << std::endl;

    auto acceleration = sf::Vector2f(0, 0);
    auto const force =
        (delta_time.asMilliseconds() * found_player->acceleration) / 1000;

    acceleration += sf::Vector2f(force * current_input.direction.x,
                                 force * current_input.direction.y);

    auto new_velocity = found_player->velocity + acceleration;
    // TODO : Note this is a damping const of 0.1. We most likley
    auto const new_damping =
        sf::Vector2f(-new_velocity.x, -new_velocity.y) * 0.1f;

    new_velocity += new_damping;
    reducer.SetEntityVelocity(new_velocity);

    auto rooms = reducer.GetState().map.rooms;

    auto room_the_player_is_in = std::find_if(
        rooms.begin(), rooms.end(), [this, found_player](const auto &room) {
           auto sprite_size = Screen::GetScale() * Map::GetSpriteSize();
            return sf::FloatRect(
                room.left * sprite_size, room.top * sprite_size,
                room.width * sprite_size, room.height * sprite_size
            ).contains(found_player->transform);
        });

    if (room_the_player_is_in == rooms.end() ||
        found_player->hitboxes.size() < 1) {
        reducer.SetEntityTransform(found_player->transform + new_velocity);
    } else {
		auto sprite_size = Screen::GetScale() * Map::GetSpriteSize();
		auto scaled_room = sf::FloatRect(
            room_the_player_is_in->left * sprite_size, 
            room_the_player_is_in->top * sprite_size,
			room_the_player_is_in->width * sprite_size, 
            room_the_player_is_in->height * sprite_size);

        reducer.SetEntityTransform(ClampToRoom(
            found_player->hitboxes[0], // TODO : Not sure what to do when we
                                       // have more than one hitbox
            scaled_room, found_player->transform,
            found_player->transform + new_velocity));
    }

    if (new_velocity.x > 0.01f || new_velocity.x < -0.01f ||
        new_velocity.y > 0.01f || new_velocity.y < -0.01f) {
        reducer.SetPlayerState(EntityState::Walking);
    } else {
        reducer.SetPlayerState(EntityState::Idle);
    }

    if (!reducer.GetState().editor_state.editor_enabled) {
        house_view.SetViewCenter(found_player->transform);
    }
    reducer.SetPlayerDirection(current_input.direction);
    HandleActions(reducer);

    auto state = reducer.GetState();
    auto current_animation = animations->find(found_player->state);
    current_animation->second.sprite.setPosition(found_player->transform);
    current_animation->second.sprite.setRotation(found_player->facing);
}

void PlayerController::HandleActions(HouseSceneReducer &) {}

void PlayerController::Reset() {
    // entity.SetVelocity(sf::Vector2f(0, 0));
}

sf::Vector2f PlayerController::ClampToRoom(sf::FloatRect player_hitbox,
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
