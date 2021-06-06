#include "EntityView.h"
#include "Animation.h"

EntityView::EntityView(const Entity& entity, const SpriteSheet& sprite_sheet, const Anim) :
animations(),
entity(entity)
{
}

void EntityView::Draw(sf::RenderTarget& target, const HouseSceneState& state) const {
    auto current_animation = animations.find(entity.GetEntityState());

    /*
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
    */

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
