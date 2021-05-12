#include "TilePaletteView.h"

TilePaletteView::TilePaletteView(SpriteSheet &tile_map, int window_height) : tile_map(tile_map), offset(20) {
    selection_rectangle = new sf::RectangleShape(sf::Vector2f(
        tile_map.SpriteSize(),
        tile_map.SpriteSize()
    ));
    selection_rectangle->setOutlineColor(sf::Color::Blue);
    selection_rectangle->setOutlineThickness(2);
    selection_rectangle->setFillColor(sf::Color::Transparent);

    // TODO : Do we need to copy these?
    tiles = new std::vector<sf::Sprite>(*tile_map.tiles);

    int left_toolbar_width = offset * 2 + tile_map.SpriteSize();
    int total_height = (tiles->size() * (tile_map.SpriteSize() + offset)) + offset;
    background = new sf::RectangleShape(sf::Vector2f(left_toolbar_width, total_height));
    background->setFillColor(sf::Color(60,60,60, 255));

    tile_palette_render_texture = new sf::RenderTexture();
    tile_palette_render_texture->create(left_toolbar_width, window_height); 
    tile_palette_view = new sf::View(sf::FloatRect(0, 0, left_toolbar_width, window_height));
}

void TilePaletteView::Update(const sf::Event & event, const sf::Vector2i) {

    selection_rectangle->setPosition((*tiles)[selected_tile_index].getPosition());
    for(int i = 0; i < tiles->size(); i ++) {
        int current_y_pos = 
            (i * tile_map.SpriteSize()) + 
            (offset * i) + offset;
        (*tiles)[i].setPosition(offset, current_y_pos);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

        // Manage Selection Changed
        int current_event_tile_index = 0;
        for(sf::Sprite t : *tiles) {
            bool in_current_bound = t.getGlobalBounds().contains(
                    tile_palette_render_texture->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))
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

        // TODO : This does not appear in the window correctly there is around 50 px of black suggesting this is too long
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
    for(sf::Sprite tile_sprite : *tiles) {
        tile_palette_render_texture->draw(tile_sprite);
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
