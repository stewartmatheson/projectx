#include "EntityView.h"
#include "Animation.h"

EntityView::EntityView(
    const SpriteSheet& sprite_sheet, 
    const std::unordered_map<EntityState, Animation>& animations) :
animations(animations) {}

void EntityView::Draw(sf::RenderTarget& target, const HouseSceneState& state) const {
    auto entities = state.entities; 
    // TODO : There has to be a better way of doing this. It might get very slow to have to 
    // search all entites all the time.
    auto found_player = std::find_if(
        entities.begin(), 
        entities.end(),
        [](const auto &entity) { return entity.GetEntityType() == EntityType::PlayerEntity; }
    );

    if (found_player == entities.end()) {
        return;
    }

    auto current_animation = animations.find(found_player->GetEntityState());
    if (current_animation == animations.end()) {
        // TODO : We might not want to do this each draw call.
        sf::RectangleShape no_sprite(sf::Vector2f(50,80));
        no_sprite.setPosition(found_player->GetTransform());
        target.draw(no_sprite);
        return;
    }

    target.draw(current_animation->second.sprite);
}
