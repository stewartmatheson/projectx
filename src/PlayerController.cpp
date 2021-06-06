#include "PlayerController.h"

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


    // TODO : not sure where this should live
    /*
    if (!state.editor_enabled) {
        player.Update(event);
        return;
    }
    */
}

void PlayerController::Update (HouseSceneReducer& state) {
    auto acceleration = entity.GetAcceleration();
    auto player_velocity = entity.GetVelocity();
    auto speed = entity.GetSpeed();
    auto new_velocity = sf::Vector2f(
        ((current_input.x * speed) - player_velocity.x) * acceleration,
        ((current_input.y * speed) - player_velocity.y) * acceleration
    ); 
    entity.SetTransform(entity.GetTransform() + new_velocity);
}


void PlayerController::Reset() {
    entity.SetVelocity(sf::Vector2f(0, 0));
}
