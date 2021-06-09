#include "HouseSceneEntityView.h"

HouseSceneEntityView::HouseSceneEntityView(const SpriteSheet& tile_map) : tile_map(tile_map) {}

void HouseSceneEntityView::Draw(sf::RenderTarget& render_target, const HouseSceneState& state) const {
    auto entities = state.entities;
    std::for_each(entities.begin(), entities.end(), [&render_target, this](const auto &entity){
        if (entity.GetEntityType() == EntityType::PlayerEntity) {
            return;
        }
        sf::Sprite sprite_to_draw(tile_map.GetSprites()[entity.GetTileMapIndex()]);
        sprite_to_draw.setRotation(entity.GetRotation());
        int half_tile_size = tile_map.GetSpriteSize() / 2;
        sprite_to_draw.setPosition(
            (entity.GetTransform().x * tile_map.GetSpriteSize()) + half_tile_size,
            (entity.GetTransform().y * tile_map.GetSpriteSize()) + half_tile_size
        );
        sprite_to_draw.setOrigin(tile_map.GetSize() / 2, tile_map.GetSize() / 2);
        render_target.draw(sprite_to_draw);
    });
}
