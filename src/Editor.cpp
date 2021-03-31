#include "Editor.h"

Editor* CreateEditor(TileMap &tile_map, int window_height, int window_width) {
    int offset = 20;
    int left_toolbar_width = offset * 2 + (tile_map.scale * tile_map.size);

    sf::RectangleShape* selection = new sf::RectangleShape();
    selection->setSize(
            sf::Vector2f(
                tile_map.size * tile_map.scale, 
                tile_map.size * tile_map.scale
                )
            );
    selection->setOutlineColor(sf::Color::Blue);
    selection->setOutlineThickness(2);
    selection->setFillColor(sf::Color::Transparent);


    Editor* editor = (Editor*)malloc(sizeof(*editor));
    editor->selection_rectangle = selection;
    editor->tiles = new std::vector<sf::Sprite>(*tile_map.tiles);
    int total_height = (editor->tiles->size() * (tile_map.scale * tile_map.size + offset)) + offset;
    sf::RectangleShape* background = new sf::RectangleShape(sf::Vector2f(left_toolbar_width, total_height));
    background->setFillColor(sf::Color(60,60,60, 255));
    editor->background = background;

    // TODO : We might need to copy here. Not sure 
    editor->tile_map = &tile_map;

    editor->offset = offset;
    editor->selected_tile_index = 0;
    editor->tile_palette_render_texture = new sf::RenderTexture();
    editor->tile_palette_render_texture->create(left_toolbar_width, window_height); 

    editor->tile_palette_view = new sf::View(sf::FloatRect(0, 0, left_toolbar_width, window_height));
    return editor;
}

void DestructEditor(Editor& editor) {
    delete editor.selection_rectangle;
    delete editor.background;
    delete editor.tiles;
    delete editor.tile_palette_view;
    free(&editor);
}

void UpdateEditor(Editor& editor, Map& map, const sf::Event& event) {
    editor.selection_rectangle->setPosition((*editor.tiles)[editor.selected_tile_index].getPosition());
    for(int i = 0; i < editor.tiles->size(); i ++) {
        int current_y_pos = 
            (i * editor.tile_map->scale * editor.tile_map->size) + 
            (editor.offset * i) + editor.offset;
        (*editor.tiles)[i].setPosition(editor.offset, current_y_pos);
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {

            // Manage Selection Changed
            int current_event_tile_index = 0;
            for(sf::Sprite t : *editor.tiles) {
                bool in_current_bound = t.getGlobalBounds().contains(
                    editor.tile_palette_render_texture->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))
                );

                if(in_current_bound) {
                    editor.selected_tile_index = current_event_tile_index;		
                }
                current_event_tile_index++;
            }

            // Managed tile map window click
            if (map.bounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                sf::Sprite new_sprite((*editor.tiles)[editor.selected_tile_index]);
                sf::Vector2i grid_position = GetTilePositionAt(
                        map, 
                        event.mouseButton.x, 
                        event.mouseButton.y, 
                        editor.tile_map->size * editor.tile_map->scale
                        );

                new_sprite.setPosition(sf::Vector2f(grid_position) * (float)(editor.tile_map->size * editor.tile_map->scale));
                map.tiles->push_back(new_sprite);
            }

        }
    }

    if (event.type == sf::Event::MouseWheelMoved && 
        event.mouseButton.x < editor.tile_palette_render_texture->getSize().x
    ) {
        int upper_scroll_center = editor.tile_palette_render_texture->getSize().y / 2;

        // TODO : This does not appear in the window correctly there is around 50 px of black suggesting this is too long
        int lower_scroll_center = editor.background->getSize().y - upper_scroll_center;

        if (event.mouseWheel.delta < 0 && editor.tile_palette_view->getCenter().y > upper_scroll_center) {
            editor.tile_palette_view->move(sf::Vector2f(0, 100 * event.mouseWheel.delta));
        }

        if (event.mouseWheel.delta > 0 && editor.tile_palette_view->getCenter().y < lower_scroll_center) {
            editor.tile_palette_view->move(sf::Vector2f(0, 100 * event.mouseWheel.delta));
        }
    }
}

void draw_grid_to_render_target(sf::RenderTarget &target, int grid_height, int grid_width, int size) {
    int total_grid_height = grid_height * size;
    int total_grid_width = grid_width * size;

    for(int row = 1; row < grid_height * size; row = row + size) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, row), sf::Color::White),
            sf::Vertex(sf::Vector2f(total_grid_width, row), sf::Color::White)
        };
        target.draw(line, 2, sf::Lines);
    }

    for(int col = 1; col < grid_width * size; col = col + size) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(col, 0), sf::Color::White),
            sf::Vertex(sf::Vector2f(col, total_grid_height), sf::Color::White)
        };
        target.draw(line, 2, sf::Lines);
    }
}

void DrawEditor(sf::RenderTarget& target, Editor& editor, const Map& map) {
    draw_grid_to_render_target(target, map.bounds.height, map.bounds.width, editor.tile_map->size * editor.tile_map->scale);

    editor.tile_palette_render_texture->setView(*editor.tile_palette_view);
    editor.tile_palette_render_texture->clear();
    editor.tile_palette_render_texture->draw(*editor.background);
    for(sf::Sprite tile_sprite : *editor.tiles) {
        editor.tile_palette_render_texture->draw(tile_sprite);
    }
    editor.tile_palette_render_texture->draw(*editor.selection_rectangle);
    editor.tile_palette_render_texture->display();
    sf::Sprite tile_palette_render_sprite(editor.tile_palette_render_texture->getTexture());

    target.draw(tile_palette_render_sprite);
}

