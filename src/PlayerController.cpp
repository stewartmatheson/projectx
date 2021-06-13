#include "PlayerController.h"

PlayerController::PlayerController() {}

void PlayerController::HandleInput (EventWithMouse event_with_mouse, HouseSceneReducer &state) {

    if (event_with_mouse.event.type == sf::Event::KeyPressed && event_with_mouse.event.key.code == sf::Keyboard::Left) {
        current_input = sf::Vector2f(-1, 0);
    }

    if (event_with_mouse.event.type == sf::Event::KeyPressed && event_with_mouse.event.key.code == sf::Keyboard::Right) {
        current_input = sf::Vector2f(1, 0);
    }

    if (event_with_mouse.event.type == sf::Event::KeyPressed && event_with_mouse.event.key.code == sf::Keyboard::Up) {
        current_input = sf::Vector2f(0, -1);
    }

    if (event_with_mouse.event.type == sf::Event::KeyPressed && event_with_mouse.event.key.code == sf::Keyboard::Down) {
        current_input = sf::Vector2f(0, 1);
    }

    if (event_with_mouse.event.type == sf::Event::KeyReleased) {
        current_input = sf::Vector2f(0, 0);
    }

}

void PlayerController::Update (HouseSceneReducer& reducer) {
    auto entities = reducer.GetState().entities;

    // TODO : There has to be a better way of doing this. It might get very slow to have to 
    // search all entites all the time.
    auto found_player = std::find_if(
        entities.begin(), 
        entities.end(),
        [](const auto &entity) { 
            return entity.GetEntityType() == EntityType::PlayerEntity; 
        }
    );

    if (found_player == entities.end()) {
        return;
    }

    auto acceleration = found_player->GetAcceleration();
    auto player_velocity = found_player->GetVelocity();
    auto speed = found_player->GetSpeed();
    auto new_velocity = sf::Vector2f(
        ((current_input.x * speed) - player_velocity.x) * acceleration,
        ((current_input.y * speed) - player_velocity.y) * acceleration
    ); 

    reducer.SetEntityVelocity(new_velocity);
    reducer.SetEntityTransform(found_player->GetTransform() + new_velocity);


    if (!reducer.GetState().editor_state.editor_enabled) {
        reducer.SetHouseViewCenter(found_player->GetTransform());
    }
}


void PlayerController::Reset() {
    std::cout << "PlayerController::Reset not implemented yet" << std::endl;
    // entity.SetVelocity(sf::Vector2f(0, 0));
}
