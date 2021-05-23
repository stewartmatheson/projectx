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
    std::for_each(tile_sprites.begin(), tile_sprites.end(), [this](sf::Sprite &sprite){ 
        tiles.push_back(TilePaletteTile{sprite, PaletteTile});
    });

    auto entity_sprites = entity_map.GetSprites();
    tiles.push_back(TilePaletteTile{entity_sprites[0], PaletteEntity, GhostEntity});
    tiles.push_back(TilePaletteTile{entity_sprites[1], PaletteEntity, DoorEntity});

 
    auto left_toolbar_width = offset * 2 + tile_map.GetSpriteSize();
    auto total_height = (tiles.size() * (tile_map.GetSpriteSize() + offset)) + offset;
    background = sf::RectangleShape(sf::Vector2f(left_toolbar_width, total_height));
    background.setFillColor(sf::Color(60,60,60, 255));

    tile_palette_render_texture.create(left_toolbar_width, window_height);
    tile_palette_view = sf::View(sf::FloatRect(0, 0, left_toolbar_width, window_height));
}

TilePaletteView::~TilePaletteView() {
}

void TilePaletteView::Update(const sf::Event & event, const sf::Vector2i) {

    selection_rectangle.setPosition(tiles[selected_tile_index].icon.getPosition());
    for(std::size_t i = 0; i < tiles.size(); i ++) {
        int current_y_pos = 
            (i * tile_map.GetSpriteSize()) + 
            (offset * i) + offset;
        tiles[i].icon.setPosition(offset, current_y_pos);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

        // Manage Selection Changed
        auto event_target_coords = tile_palette_render_texture.mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        auto found = std::find_if(tiles.begin(), tiles.end(), [event_target_coords](const auto &t) {
            return t.icon.getGlobalBounds().contains(event_target_coords);
        });
        if (found != tiles.end()) {
            selected_tile_index = found - tiles.begin();
        }
    }

    if (event.type == sf::Event::MouseWheelMoved && 
        (unsigned int)event.mouseButton.x < tile_palette_render_texture.getSize().x
    ) {
        int upper_scroll_center = tile_palette_render_texture.getSize().y / 2;
        int lower_scroll_center = background.getSize().y - upper_scroll_center;

        if (event.mouseWheel.delta < 0 && tile_palette_view.getCenter().y > upper_scroll_center) {
            tile_palette_view.move(0, 100 * event.mouseWheel.delta);
        }

        if (event.mouseWheel.delta > 0 && tile_palette_view.getCenter().y < lower_scroll_center) {
            tile_palette_view.move(0, 100 * event.mouseWheel.delta);
        }
    }

}

void TilePaletteView::Draw(sf::RenderTarget &target) {
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


int TilePaletteView::GetSelectedTileIndex() const {
    return selected_tile_index;
}

const TilePaletteTile& TilePaletteView::GetSelectedTile() const {
    return tiles[selected_tile_index];
}

const sf::RectangleShape &TilePaletteView::GetBackground() const {
    return background;
}
