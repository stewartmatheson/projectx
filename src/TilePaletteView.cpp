#include "TilePaletteView.h"

TilePaletteView::TilePaletteView(
    SpriteSheet&, 
    SpriteSheet&, 
    sf::RenderTexture& tile_palette_render_texture, 
    int
) :
tile_palette_render_texture(tile_palette_render_texture)
{}

void TilePaletteView::Draw(sf::RenderTarget& target, const HouseSceneState& state) const {

    if (!state.editor_state.editor_enabled) {
        return;
    }
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
}

/*
TilePaletteView::TilePaletteView(
    SpriteSheet &tile_map, 
    SpriteSheet &entity_map, 
    int window_height
) : 
offset(20),
selected_tile_index(0),
selection_rectangle(sf::Vector2f(tile_map.GetSpriteSize(), tile_map.GetSpriteSize())),
tile_map(tile_map), 
entity_map(entity_map) {

    auto entity_sprites = entity_map.GetSprites();
    tiles.push_back(TilePaletteTile{entity_sprites[0], PaletteEntity, EntityType::GhostEntity});
    tiles.push_back(TilePaletteTile{entity_sprites[1], PaletteEntity, EntityType::DoorEntity});

    for(std::size_t i = 0; i < tiles.size(); i ++) {
        auto y = (i * tile_map.GetSpriteSize()) + (offset * i) + offset;
        tiles[i].icon.setPosition(offset, y);
    }
    selection_rectangle.setPosition(tiles[selected_tile_index].icon.getPosition());


}

TilePaletteView::~TilePaletteView() {}


void TilePaletteView::Draw(sf::RenderTarget &target) {

    selection_rectangle.setPosition(tiles[selected_tile_index].icon.getPosition());

    tile_palette_render_texture.setView(tile_palette_view);
    tile_palette_render_texture.clear();
    tile_palette_render_texture.draw(background);
    for(const auto &tile : tiles) {
        tile_palette_render_texture.draw(tile.icon);
    }
    tile_palette_render_texture.draw(selection_rectangle);
    tile_palette_render_texture.display();
    sf::Sprite tile_palette_render_sprite(tile_palette_render_texture.getTexture());
    target.draw(tile_palette_render_sprite);
}

*/
