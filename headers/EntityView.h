#pragma once

#include "HouseScene.h"
#include "Entity.h"

class EntityView : public View<HouseSceneState> {
    const Entity& entity;
    const std::unordered_map<EntityState, Animation>& animations;
public:
    EntityView(
        const Entity& entity, 
        const SpriteSheet& sprite_sheet,
        const std::unordered_map<EntityState, Animation>&
    );
    void Draw(sf::RenderTarget& render_target, const HouseSceneState& state) const;
};
