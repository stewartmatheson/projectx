#include "EntityView.h"
#include "Animation.h"

EntityView::EntityView(
    const Entity& entity, 
    const SpriteSheet& sprite_sheet, 
    const std::unordered_map<EntityState, Animation>& animations) :
entity(entity),
animations(animations) {}

void EntityView::Draw(sf::RenderTarget& target, const HouseSceneState& state) const {
    auto current_animation = animations.find(entity.GetEntityState());

    if (current_animation == animations.end()) {
        // TODO : We might not want to do this each draw call.
        sf::RectangleShape no_sprite(sf::Vector2f(50,80));
        no_sprite.setPosition(entity.GetTransform());
        target.draw(no_sprite);
        return;
    }

    target.draw(current_animation->second.sprite);
}
