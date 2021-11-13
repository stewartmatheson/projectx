#include "AIController.h"
#include <optional>

void AIController::Update(HouseSceneReducer &reducer, sf::Time time) {
    for(Entity entity : reducer.GetState().entities) {
        if (entity.type == EntityType::GhostEntity)  {
            ProcessEntity(entity, reducer, time);
        }
    }
}

void AIController::ProcessEntity (Entity &entity, HouseSceneReducer& reducer, sf::Time time) {
    std::shared_ptr<Entity> target = entity.ai.target.lock();
    if(!target) {
        return;
    }

    if (entity.ai.state == AIState::None) {
        reducer.InitEntityAIState(entity);
    }

    if (entity.ai.state == AIState::Attacking) {
        if (InAttackRange()) {
            // Figure out how to enter attack state
        } else {
            const sf::Vector2f new_position = Physics::StepPosition(
                entity, target->transform, time, reducer.GetState().map.rooms);
            reducer.MoveEntity(entity, target->transform);
        }
        return;
    }
    
    if (entity.ai.state == AIState::Patrolling) {
        auto resolved_target = VisibleTarget();
        if (resolved_target.has_value()) {
            reducer.Attack(entity, *(resolved_target->get()));
        }
    }
}
    
void AIController::HandleInput(const EventWithMouse &, HouseSceneReducer &) {
    std::cout << "Handle Input" << std::endl;
}

bool AIController::InAttackRange() const {
    return false;
}

std::optional<std::shared_ptr<Entity>> AIController::VisibleTarget() const {
    return std::nullopt;
}
