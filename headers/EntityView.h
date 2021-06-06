#pragma once

#include "HouseScene.h"
#include "Entity.h"

class EntityView : public View<HouseSceneState> {
    std::unordered_map<EntityState, Animation> animations;
    const Entity& entity;
public:
    EntityView(const Entity& entity, const SpriteSheet& sprite_sheet);
    void Draw(sf::RenderTarget& render_target, const HouseSceneState& state) const;
};

