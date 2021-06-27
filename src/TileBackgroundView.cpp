#include "TileBackgroundView.h"

TileBackgroundView::TileBackgroundView(const SpriteSheet &tile_map)
    : tile_map(tile_map) {}

void TileBackgroundView::Draw(sf::RenderTarget &render_target,
                              const HouseSceneState &state) const {
    // TODO  : Fix this raw loop
    for (const auto &tile_layer : state.tile_layers) {
        for (const auto &tile : tile_layer.tiles) {
            sf::Sprite sprite_to_draw(
                tile_map.GetSprites()[tile.tile_map_index]);
            sprite_to_draw.setRotation(tile.rotation);
            int half_tile_size = tile_map.GetSpriteSize() / 2;
            sprite_to_draw.setPosition(
                (tile.x * tile_map.GetSpriteSize()) + half_tile_size,
                (tile.y * tile_map.GetSpriteSize()) + half_tile_size);
            sprite_to_draw.setOrigin(tile_map.GetSize() / 2,
                                     tile_map.GetSize() / 2);
            render_target.draw(sprite_to_draw);
        }
    }
}
