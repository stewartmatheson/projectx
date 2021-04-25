#include <math.h>
#include <fstream>
#include "RoomScene.h"

RoomScene::RoomScene(TileMap &tile_map, int window_height, int window_width, Room* room) {
    int offset = 20;
    int left_toolbar_width = offset * 2 + tile_map.tileSize();

    sf::RectangleShape* selection = new sf::RectangleShape();
    selection->setSize(sf::Vector2f(tile_map.tileSize(), tile_map.tileSize()));
    selection->setOutlineColor(sf::Color::Blue);
    selection->setOutlineThickness(2);
    selection->setFillColor(sf::Color::Transparent);


    this->selection_rectangle = selection;
    this->tiles = new std::vector<sf::Sprite>(*tile_map.tiles);
    int total_height = (this->tiles->size() * (tile_map.tileSize() + offset)) + offset;
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
    this->room = room;
}

RoomScene::~RoomScene() {
    delete selection_rectangle;
    delete background;
    delete tiles;
    delete tile_palette_view;
    delete current_mouse_grid_position;
    delete room_render_texture;
    delete room_view;
}

void RoomScene::UpdateEditor(const sf::Event& event, const sf::Vector2i current_mouse_position) {
    selection_rectangle->setPosition((*tiles)[selected_tile_index].getPosition());
    for(int i = 0; i < tiles->size(); i ++) {
        int current_y_pos = 
            (i * tile_map->scale * tile_map->size) + 
            (offset * i) + offset;
        (*tiles)[i].setPosition(offset, current_y_pos);
    }

    sf::Vector2f current_target_coords = room_render_texture->mapPixelToCoords(
            sf::Vector2i(current_mouse_position.x, current_mouse_position.y)
    );

    current_mouse_grid_position->x = floor(current_target_coords.x / (tile_map->size * tile_map->scale));
    current_mouse_grid_position->y = floor(current_target_coords.y / (tile_map->size * tile_map->scale));
     
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
        
        sf::Vector2f event_target_coords = room_render_texture->mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        
        sf::IntRect pixel_bounds = sf::IntRect(
            0, 
            0, 
            this->room->bounds.width * tile_map->size * tile_map->scale,
            this->room->bounds.height * tile_map->size * tile_map->scale
        );


        if (pixel_bounds.contains(sf::Vector2i(event_target_coords.x, event_target_coords.y)) && 
            !background->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))
        ) {


            for (auto it = this->room->tiles->begin(); it != this->room->tiles->end(); ) {
                sf::FloatRect current_tile_bounds = sf::FloatRect(
                    it->x * (tile_map->size * tile_map->scale),
                    it->y * (tile_map->size * tile_map->scale),
                    tile_map->size * tile_map->scale,
                    tile_map->size * tile_map->scale
                );
                
                if (current_tile_bounds.contains(event_target_coords)) {
                    this->room->tiles->erase(it);
                    break;
                } else {
                    ++it;
                }
            }

            this->room->tiles->push_back(
                Tile { 
                    (int)floor(event_target_coords.x / (tile_map->size * tile_map->scale)),
                    (int)floor(event_target_coords.y / (tile_map->size * tile_map->scale)),
                    (int)current_rotation,
                    selected_tile_index 
                }
            );
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

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
        this->room->WriteRoomToFile("./assets/maps/room.bin");
    }

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
        panning = false;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        panning = true;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle) {
        current_rotation += 90;
    }

    sf::Vector2i mouse_delta = sf::Vector2i(
        current_mouse_position.x - last_mouse_position.x, 
        current_mouse_position.y - last_mouse_position.y
    );

    last_mouse_position = current_mouse_position;

    if (panning) {
        room_view->move(sf::Vector2f(mouse_delta.x * -1, mouse_delta.y * -1));
    }

    if (event.type == sf::Event::Resized) {
        std::cout << event.size.width << std::endl;
        room_view->setSize(event.size.width, event.size.height);
        room_render_texture = new sf::RenderTexture();
        room_render_texture->create(event.size.width, event.size.height); 
    }
 
}

void DrawGrid(sf::RenderTarget &target, int grid_height, int grid_width, int size) {
    int total_grid_height = grid_height * size;
    int total_grid_width = grid_width * size;

    for(int row = 1; row < (grid_height +1) * size; row = row + size) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, row), sf::Color::White),
            sf::Vertex(sf::Vector2f(total_grid_width, row), sf::Color::White)
        };
        target.draw(line, 2, sf::Lines);
    }

    for(int col = 1; col < (grid_width + 1) * size; col = col + size) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(col, 0), sf::Color::White),
            sf::Vertex(sf::Vector2f(col, total_grid_height), sf::Color::White)
        };
        target.draw(line, 2, sf::Lines);
    }
}

void RoomScene::DrawEditor(sf::RenderTarget& target) {
    // Draw Room and Grid
    room_render_texture->setView(*room_view);
    room_render_texture->clear();
    this->room->DrawRoom(*room_render_texture, *tile_map);
    DrawGrid(
        *room_render_texture, 
        this->room->bounds.height, 
        this->room->bounds.width, 
        tile_map->size * tile_map->scale
    );

    // Draw Selected Tile
    sf::Sprite selected_tile_sprite((*tile_map->tiles)[selected_tile_index]);
    selected_tile_sprite.setScale(sf::Vector2f(tile_map->scale, tile_map->scale));
    int half_tile_size = tile_map->size * tile_map->scale / 2;
    selected_tile_sprite.setPosition(
        (current_mouse_grid_position->x * tile_map->size * tile_map->scale) + half_tile_size,
        (current_mouse_grid_position->y * tile_map->size * tile_map->scale) + half_tile_size
    );
    selected_tile_sprite.setColor(sf::Color(255, 255, 255, 170));
    selected_tile_sprite.setOrigin(tile_map->size / 2, tile_map->size / 2);
    selected_tile_sprite.rotate(current_rotation);
    room_render_texture->draw(selected_tile_sprite);

    room_render_texture->display();

    sf::Sprite room_render_sprite(room_render_texture->getTexture());

    sf::View current_window_view = target.getView();
    target.draw(room_render_sprite);

    //Draw Tile Palette
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