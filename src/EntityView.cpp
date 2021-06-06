#include "EntityView.h"
#include "Animation.h"

EntityView::EntityView(const Entity& entity, const SpriteSheet& sprite_sheet) :
entity(entity),
animations()
{
    std::vector<AnimationFrame> idle_frames;
    for (auto col = 0; col < 10; col++) {
        idle_frames.push_back(AnimationFrame{col, 0});
    }

    std::vector<AnimationFrame> throw_frames;
    for (auto col = 0; col < 10; col++) {
        throw_frames.push_back(AnimationFrame{col, 1});
    }

    std::vector<AnimationFrame> walk_frames;
    for (auto col = 0; col < 10; col++) {
        walk_frames.push_back(AnimationFrame{col, 2});
    }

    std::vector<AnimationFrame> attack_frames;
    for (auto col = 0; col < 10; col++) {
        attack_frames.push_back(AnimationFrame{col, 3});
    }

    std::vector<AnimationFrame> die_frames;
    for (auto col = 0; col < 10; col++) {
        die_frames.push_back(AnimationFrame{col, 4});
    }

    animations.insert(
        {EntityState::Idle, Animation(sprite_sheet, idle_frames, 32, 32, 8)}
    );

    animations.insert(
        {EntityState::Throwing, Animation(sprite_sheet, throw_frames, 32, 32, 8) }
    );

    animations.insert(
        {EntityState::Walking, Animation(sprite_sheet, walk_frames, 32, 32, 8) }
    );

    animations.insert(
        {EntityState::Attacking, Animation(sprite_sheet, attack_frames, 32, 32, 8) }
    );

    animations.insert(
        {EntityState::Dying, Animation(sprite_sheet, die_frames, 32, 32, 8) }
    );
}

void EntityView::Draw(sf::RenderTarget& target, const HouseSceneState& state) const {
    auto current_animation = animations.find(entity.GetEntityState());

    if (entity.GetFacingLeft()) {
        current_animation->second.sprite.setScale(
            -4,
            current_animation->second.sprite.getScale().y
        );
    } else {
        current_animation->second.sprite.setScale(
            4,
            current_animation->second.sprite.getScale().y
        );
    } 

    if (current_animation == animations.end()) {
        // TODO : We might not want to do this each draw call.
        sf::RectangleShape no_sprite(sf::Vector2f(50,80));
        no_sprite.setPosition(entity.GetTransform());
        target.draw(no_sprite);
        return;
    }

    current_animation->second.Update();
    current_animation->second.sprite.setPosition(entity.GetTransform());
    target.draw(current_animation->second.sprite);
}
