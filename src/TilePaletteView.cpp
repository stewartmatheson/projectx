#include "TilePaletteView.h"

TilePaletteView::TilePaletteView(
    SpriteSheet& tile_map, 
    SpriteSheet& entity_map, 
    int width,
    int height
) { 
    tile_palette_render_texture.create(width, height);
}

void TilePaletteView::Draw(sf::RenderTarget& target, const HouseSceneState& state) const {
    if (!state.editor_state.editor_enabled) {
        return;
    }
    target.draw(state.editor_state.tile_palette_background);
    for (const auto &tile : state.editor_state.tile_palette_tiles)
    {
        target.draw(tile.icon);
    }
    target.draw(state.editor_state.tile_palette_selection_rectangle);

    /*
    tile_palette_render_texture.setView(state.editor_state.tile_palette_view);
    tile_palette_render_texture.clear();
    tile_palette_render_texture.draw(state.editor_state.tile_palette_background);

    for (const auto &tile : state.editor_state.tile_palette_tiles)
    {
        tile_palette_render_texture.draw(tile.icon);
    }

    tile_palette_render_texture.draw(state.editor_state.tile_palette_selection_rectangle);
    tile_palette_render_texture.display();
    sf::Sprite tile_palette_render_sprite(tile_palette_render_texture.getTexture());
    target.draw(tile_palette_render_sprite);
    */
}
