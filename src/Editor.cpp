#include <math.h>
#include <fstream>
#include "Editor.h"

Editor::Editor(TileMap &tile_map, int window_height, int window_width) {
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


    this->selection_rectangle = selection;
    this->tiles = new std::vector<sf::Sprite>(*tile_map.tiles);
    int total_height = (this->tiles->size() * (tile_map.scale * tile_map.size + offset)) + offset;
    sf::RectangleShape* background = new sf::RectangleShape(sf::Vector2f(left_toolbar_width, total_height));
    background->setFillColor(sf::Color(60,60,60, 255));
    this->background = background;

    // TODO : We might need to copy here. Not sure 
    this->tile_map = &tile_map;

    this->offset = offset;
    this->selected_tile_index = 0;

    this->tile_palette_render_texture = new sf::RenderTexture();
    this->tile_palette_render_texture->create(left_toolbar_width, window_height); 
    this->tile_palette_view = new sf::View(sf::FloatRect(0, 0, left_toolbar_width, window_height));

    this->room_render_texture = new sf::RenderTexture();
    this->room_render_texture->create(window_width, window_height); 
    this->room_view = new sf::View(sf::FloatRect(0, 0, window_height, window_height));

    this->current_mouse_grid_position = new sf::Vector2i();
    this->panning = false;
    this->last_mouse_position = sf::Vector2i();
    this->current_rotation = 0;
}

Editor::~Editor() {
    delete selection_rectangle;
    delete background;
    delete tiles;
    delete tile_palette_view;
    delete current_mouse_grid_position;
    delete room_render_texture;
    delete room_view;
}

void UpdateEditor(Editor& editor, const sf::Event& event, Room& room, const sf::Vector2i current_mouse_position) {
    editor.selection_rectangle->setPosition((*editor.tiles)[editor.selected_tile_index].getPosition());
    for(int i = 0; i < editor.tiles->size(); i ++) {
        int current_y_pos = 
            (i * editor.tile_map->scale * editor.tile_map->size) + 
            (editor.offset * i) + editor.offset;
        (*editor.tiles)[i].setPosition(editor.offset, current_y_pos);
    }

    sf::Vector2f current_target_coords = editor.room_render_texture->mapPixelToCoords(
            sf::Vector2i(current_mouse_position.x, current_mouse_position.y)
    );

    editor.current_mouse_grid_position->x = floor(current_target_coords.x / (editor.tile_map->size * editor.tile_map->scale));
    editor.current_mouse_grid_position->y = floor(current_target_coords.y / (editor.tile_map->size * editor.tile_map->scale));
     
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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
        
        sf::Vector2f event_target_coords = editor.room_render_texture->mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        
        sf::IntRect pixel_bounds = sf::IntRect(
            0, 
            0, 
            room.bounds.width * editor.tile_map->size * editor.tile_map->scale,
            room.bounds.height * editor.tile_map->size * editor.tile_map->scale
        );

        if (pixel_bounds.contains(sf::Vector2i(event_target_coords.x, event_target_coords.y))) {
            room.tiles->push_back(
                Tile { 
                    (int)floor(event_target_coords.x / (editor.tile_map->size * editor.tile_map->scale)),
                    (int)floor(event_target_coords.y / (editor.tile_map->size * editor.tile_map->scale)),
                    (int)editor.current_rotation,
                    editor.selected_tile_index 
                }
            );
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

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
        WriteRoomToFile(room, "./assets/maps/room.bin");
    }

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
        editor.panning = false;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        editor.panning = true;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle) {
        editor.current_rotation += 90;
    }

    sf::Vector2i mouse_delta = sf::Vector2i(
        current_mouse_position.x - editor.last_mouse_position.x, 
        current_mouse_position.y - editor.last_mouse_position.y
    );

    editor.last_mouse_position = current_mouse_position;

    if (editor.panning) {
        editor.room_view->move(sf::Vector2f(mouse_delta.x * -1, mouse_delta.y * -1));
    }

}

void DrawGrid(sf::RenderTarget &target, int grid_height, int grid_width, int size) {
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

void DrawEditor(sf::RenderTarget& target, Editor& editor, Room& room) {
    // Draw Room and Grid
    editor.room_render_texture->setView(*editor.room_view);
    editor.room_render_texture->clear();
    DrawRoom(*editor.room_render_texture, room, *editor.tile_map);
    DrawGrid(*editor.room_render_texture, room.bounds.height, room.bounds.width, editor.tile_map->size * editor.tile_map->scale);

    // Draw Selected Tile
    sf::Sprite selected_tile_sprite((*editor.tile_map->tiles)[editor.selected_tile_index]);
    selected_tile_sprite.setScale(sf::Vector2f(editor.tile_map->scale, editor.tile_map->scale));
    int half_tile_size = editor.tile_map->size * editor.tile_map->scale / 2;
    selected_tile_sprite.setPosition(
        (editor.current_mouse_grid_position->x * editor.tile_map->size * editor.tile_map->scale) + half_tile_size,
        (editor.current_mouse_grid_position->y * editor.tile_map->size * editor.tile_map->scale) + half_tile_size
    );
    selected_tile_sprite.setColor(sf::Color(255, 255, 255, 170));
    selected_tile_sprite.setOrigin(editor.tile_map->size / 2, editor.tile_map->size / 2);
    selected_tile_sprite.rotate(editor.current_rotation);
    editor.room_render_texture->draw(selected_tile_sprite);

    editor.room_render_texture->display();
    sf::Sprite room_render_sprite(editor.room_render_texture->getTexture());
    target.draw(room_render_sprite);

    //Draw Tile Palette
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

void WriteRoomToFile(Room& room, std::string file_name) {
    std::ofstream wf(file_name, std::ios::out | std::ios::binary);

    if(!wf) {
        std::cout << "Can't open file!" << std::endl;
        exit(1);
    }

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.left), 
        sizeof (room.bounds.left)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.top), 
        sizeof (room.bounds.top)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.width), 
        sizeof (room.bounds.width)
    );

    wf.write(
        reinterpret_cast<const char *>(&room.bounds.height), 
        sizeof (room.bounds.height)
    );

    int room_tile_count = room.tiles->size();
    wf.write(reinterpret_cast<const char *>(&room_tile_count), sizeof (room_tile_count));

    for(int i = 0; i < room_tile_count; i++) {
        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].rotation), 
            sizeof ((*room.tiles)[i].rotation)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].tile_map_index), 
            sizeof ((*room.tiles)[i].tile_map_index)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].x), 
            sizeof ((*room.tiles)[i].x)
        );

        wf.write(
            reinterpret_cast<const char *>(&(*room.tiles)[i].y), 
            sizeof ((*room.tiles)[i].y)
        );
    }
}
