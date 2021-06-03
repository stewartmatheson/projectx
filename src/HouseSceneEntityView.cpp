#include "HouseSceneEntityView.h"

void HouseSceneEntityView::Draw(sf::RenderTarget& render_target, const HouseSceneState& state) {
    auto entities = state.entities;
    std::for_each(entities.begin(), entities.end(), [&render_target, this](const auto &entity){
        sf::Sprite sprite_to_draw(entity_map.GetSprites()[entity.GetTileMapIndex()]);
        sprite_to_draw.setRotation(entity.GetRotation());
        int half_tile_size = entity_map.GetSpriteSize() / 2;
        sprite_to_draw.setPosition(
            (entity.GetTransform().x * entity_map.GetSpriteSize()) + half_tile_size,
            (entity.GetTransform().y * entity_map.GetSpriteSize()) + half_tile_size
        );
        sprite_to_draw.setOrigin(entity_map.GetSize() / 2, entity_map.GetSize() / 2);
        render_target.draw(sprite_to_draw);
    });
}
