#include "SelectedTileView.h"

SelectedTileView::SelectedTileView(int sprite_size) : sprite_size(sprite_size) {}

void SelectedTileView::Draw(sf::RenderTarget& render_target, const HouseSceneState& state) {
    if (!state.editor_enabled) {
        return;
    }

    // Draw Selected Tile
    auto selected_tile_sprite = tile_palette_view.GetSelectedTile().icon;
    int half_tile_size = sprite_size / 2;
    selected_tile_sprite.setPosition(
        (current_mouse_grid_position.x * sprite_size) + half_tile_size,
        (current_mouse_grid_position.y * sprite_size) + half_tile_size
    );
    selected_tile_sprite.setColor(sf::Color(255, 255, 255, 170));
    selected_tile_sprite.setOrigin(sprite_size / 2, sprite_size / 2);
    selected_tile_sprite.rotate(state.selected_tile_rotation);

    render_target.draw(selected_tile_sprite);
}
