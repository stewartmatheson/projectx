
#pragma once

#include "Controller.h"
#include "Map.h"
#include "EventWithMouse.h"
#include "HouseSceneReducer.h"
#include "ControllerScheme.h"
#include "ViewLayer.h"
#include <unordered_map>

class PlayerController : public Controller<HouseSceneReducer> {
    ControllerSchemeState current_input;
    std::shared_ptr<std::unordered_map<EntityState, Animation>> animations;
    sf::Vector2f ClampToRoom(sf::FloatRect, sf::FloatRect, sf::Vector2f, sf::Vector2f);
    std::shared_ptr<ControllerScheme> controller_scheme;
    void HandleActions(HouseSceneReducer &);
    ViewLayer& house_view;

  public:
    PlayerController(
        std::shared_ptr<std::unordered_map<EntityState, Animation>>, 
        std::shared_ptr<ControllerScheme>,
        ViewLayer&
    );
    void Update(HouseSceneReducer &, sf::Time);
    void HandleInput(const EventWithMouse &, HouseSceneReducer &);
    void Reset();
};
