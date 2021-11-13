#pragma once

#include <optional>

#include "HouseSceneReducer.h"
#include "EventWithMouse.h"
#include "Controller.h"
#include "Entity.h"
#include "Map.h"
#include "Physics.h"

class AIController : public Controller<HouseSceneReducer> {
    void ProcessEntity(Entity&, HouseSceneReducer&, sf::Time);
    bool InAttackRange() const;
    std::optional<std::shared_ptr<Entity>> VisibleTarget() const;
public:
    void Update(HouseSceneReducer &, sf::Time);
    void HandleInput(const EventWithMouse &, HouseSceneReducer &);
};
