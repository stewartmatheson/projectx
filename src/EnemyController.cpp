#include <algorithm>
#include "EnemyController.h"
#include "EntityFactory.h"

void EnemyController::Update(HouseSceneReducer &reducer, sf::Time time) {
    auto state = reducer.GetState();
    auto menace = CalculateMenace(state);

    // Spawn more enemies according to menace
    auto enemy_count = 0;
    for (auto entity : state.entities) {
        if (entity.type == EntityType::GhostEntity) {
            enemy_count++;
        }
    }

    auto max_enemy_count = 100;
    auto desired_enemy_count = menace * max_enemy_count;
    for (auto i = 0; desired_enemy_count < enemy_count; i++) {
        reducer.AddEntity(EntityFactory::Ghost());
    }

    for (auto entity : state.entities) {
        if (entity.type == EntityType::GhostEntity) {
            UpdateEntity(entity, menace);
        }
    }
}


float EnemyController::CalculateMenace(HouseSceneState &state) {
    /*
        Factors to include here.
        GameClock will raise floor.
        Amount of Enemies
        Current enemey jobs

    */
    auto loot_value_in_last_minute = 0;
    auto menance = 0.0f;

    // TODO : Do we have this???
    auto menance_floor_form_game_clock = 0.1f;

    return std::clamp(menance, menance_floor_form_game_clock, 1.0f);
}

EnemyJob EnemyController::TreverseTreeForCurrentJob() {

}

void EnemyController::UpdateEntity(Entity& entity, int menace) {
    auto current_job = TreverseTreeForCurrentJob(entity);
    auto transform = TransformForJob(current_job);
}

void EnemyController::HandleInput(const EventWithMouse &event_with_mouse, HouseSceneReducer &reducer) {}
