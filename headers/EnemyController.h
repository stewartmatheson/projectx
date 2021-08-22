#pragma once

#include "Controller.h"
#include "HouseSceneReducer.h"

enum class EnemyJob { Patrolling, Swarming, Attacking };

class EnemyController : public Controller<HouseSceneReducer> {
    float CalculateMenace(HouseSceneState&);
    void UpdateEntity(Entity&, int);
    EnemyJob TreverseTreeForCurrentJob();
  public:
    void Update(HouseSceneReducer &, sf::Time);
    void HandleInput(const EventWithMouse &, HouseSceneReducer &);
};
