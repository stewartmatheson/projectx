#include "TilePaletteView.h"

TilePaletteView::TilePaletteView(
    SpriteSheet &tile_map, 
    int window_height
) : tile_map(tile_map), offset(20), selected_tile_index(0) {

    selection_rectangle = new sf::RectangleShape(sf::Vector2f(
        tile_map.SpriteSize(),
        tile_map.SpriteSize()
    ));
    selection_rectangle->setOutlineColor(sf::Color::Blue);
    selection_rectangle->setOutlineThickness(2);
    selection_rectangle->setFillColor(sf::Color::Transparent);

    for (auto it = tile_map.tiles->begin(); it != tile_map.tiles->end(); ) {
        tiles.push_back(TilePaletteTile{*it, PaletteTile});
        ++it;
    }
 
    auto door_palette_sprite_icon = CreateIconSprite(tile_map.SpriteSize(), sf::Color::Red);
    tiles.push_back(TilePaletteTile{door_palette_sprite_icon, PaletteEntity, DoorEntity });

    auto ghost_palette_sprite_icon = CreateIconSprite(tile_map.SpriteSize(), sf::Color::Green);
    tiles.push_back(TilePaletteTile{ghost_palette_sprite_icon, PaletteEntity, GhostEntity });

    auto left_toolbar_width = offset * 2 + tile_map.SpriteSize();
    auto total_height = (tiles.size() * (tile_map.SpriteSize() + offset)) + offset;
    background = new sf::RectangleShape(sf::Vector2f(left_toolbar_width, total_height));
    background->setFillColor(sf::Color(60,60,60, 255));

    tile_palette_render_texture = new sf::RenderTexture();
    tile_palette_render_texture->create(left_toolbar_width, window_height); 
    tile_palette_view = new sf::View(sf::FloatRect(0, 0, left_toolbar_width, window_height));
}

TilePaletteView::~TilePaletteView() {
    delete background;
    delete selection_rectangle;
    delete tile_palette_render_texture;
    delete tile_palette_view;
}

sf::Sprite TilePaletteView::CreateIconSprite(int sprite_size, sf::Color color) {
    auto icon_sprite_render_texture = new sf::RenderTexture(); 
    icon_sprite_render_texture->create(sprite_size, sprite_size);
    auto icon_sprite = sf::RectangleShape(sf::Vector2f(sprite_size, sprite_size));
    icon_sprite.setFillColor(color);
    icon_sprite_render_texture->draw(icon_sprite);
    return sf::Sprite(icon_sprite_render_texture->getTexture());
}

void TilePaletteView::Update(const sf::Event & event, const sf::Vector2i) {

    selection_rectangle->setPosition(tiles[selected_tile_index].icon.getPosition());
    for(auto i = 0; i < tiles.size(); i ++) {
        int current_y_pos = 
            (i * tile_map.SpriteSize()) + 
            (offset * i) + offset;
        tiles[i].icon.setPosition(offset, current_y_pos);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

        // Manage Selection Changed
        int current_event_tile_index = 0;
        for(auto t : tiles) {
            bool in_current_bound = t.icon.getGlobalBounds().contains(
                tile_palette_render_texture->mapPixelToCoords(
                    sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
                )
            );

            if(in_current_bound) {
                selected_tile_index = current_event_tile_index;		
            }
            current_event_tile_index++;
        }
    }

    if (event.type == sf::Event::MouseWheelMoved && 
        event.mouseButton.x < tile_palette_render_texture->getSize().x
    ) {
        int upper_scroll_center = tile_palette_render_texture->getSize().y / 2;
        int lower_scroll_center = background->getSize().y - upper_scroll_center;

        if (event.mouseWheel.delta < 0 && tile_palette_view->getCenter().y > upper_scroll_center) {
            tile_palette_view->move(sf::Vector2f(0, 100 * event.mouseWheel.delta));
        }

        if (event.mouseWheel.delta > 0 && tile_palette_view->getCenter().y < lower_scroll_center) {
            tile_palette_view->move(sf::Vector2f(0, 100 * event.mouseWheel.delta));
        }
    }

}

void TilePaletteView::Draw(sf::RenderTarget &target) {
    tile_palette_render_texture->setView(*tile_palette_view);
    tile_palette_render_texture->clear();
    tile_palette_render_texture->draw(*background);
    for(auto tile : tiles) {
        tile_palette_render_texture->draw(tile.icon);
    }
    tile_palette_render_texture->draw(*selection_rectangle);
    tile_palette_render_texture->display();
    sf::Sprite tile_palette_render_sprite(tile_palette_render_texture->getTexture());
    target.draw(tile_palette_render_sprite);
}


int TilePaletteView::GetSelectedTileIndex() {
    return selected_tile_index;
}

sf::RectangleShape* TilePaletteView::GetBackground() {
    return background;
}
