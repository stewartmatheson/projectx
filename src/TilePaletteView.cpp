#include "TilePaletteView.h"

TilePaletteView::TilePaletteView(int width, int height) {
    tile_palette_render_texture.create(width, height);
}

void TilePaletteView::Draw(sf::RenderTarget &target,
                           const HouseSceneState &state) const {
    if (!state.editor_state.editor_enabled) {
        return;
    }
    target.draw(state.editor_state.tile_palette_background);
    for (const auto &tile : state.editor_state.tile_palette_tiles) {
        target.draw(tile.icon);
    }
    target.draw(state.editor_state.tile_palette_selection_rectangle);
}

void TilePaletteView::Update() {}
