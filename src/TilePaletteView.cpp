#include "TilePaletteView.h"

TilePaletteView::TilePaletteView(
    SpriteSheet &tile_map, 
    SpriteSheet &entity_map, 
    int window_height
) : offset(20),
    selected_tile_index(0),
    selection_rectangle(sf::Vector2f(tile_map.GetSpriteSize(), tile_map.GetSpriteSize())),
    tile_map(tile_map), 
    entity_map(entity_map) {

    selection_rectangle.setOutlineColor(sf::Color::Blue);
    selection_rectangle.setOutlineThickness(2);
    selection_rectangle.setFillColor(sf::Color::Transparent);

    auto tile_sprites = tile_map.GetSprites();
    std::for_each(tile_sprites.begin(), tile_sprites.end(), [this](const auto &sprite){ 
        tiles.push_back(TilePaletteTile{sprite, PaletteTile});
    });

    auto entity_sprites = entity_map.GetSprites();
    tiles.push_back(TilePaletteTile{entity_sprites[0], PaletteEntity, EntityType::GhostEntity});
    tiles.push_back(TilePaletteTile{entity_sprites[1], PaletteEntity, EntityType::DoorEntity});

    for(std::size_t i = 0; i < tiles.size(); i ++) {
        auto y = (i * tile_map.GetSpriteSize()) + (offset * i) + offset;
        tiles[i].icon.setPosition(offset, y);
    }
    selection_rectangle.setPosition(tiles[selected_tile_index].icon.getPosition());

    auto left_toolbar_width = offset * 2 + tile_map.GetSpriteSize();
    auto total_height = (tiles.size() * (tile_map.GetSpriteSize() + offset)) + offset;
    background = sf::RectangleShape(sf::Vector2f(left_toolbar_width, total_height));
    background.setFillColor(sf::Color(60,60,60, 255));

    tile_palette_render_texture.create(left_toolbar_width, window_height);
    tile_palette_view = sf::View(sf::FloatRect(0, 0, left_toolbar_width, window_height));
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

