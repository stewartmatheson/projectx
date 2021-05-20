#include <math.h>
#include <fstream>
#include "HouseScene.h"

HouseScene::HouseScene(
        SpriteSheet &tile_map, 
        int window_height, 
        int window_width, 
        House &house, 
        Entity &player
) : current_rotation(0), 
    editor_enabled(true), 
    house(house), 
    house_view(sf::FloatRect(0, 0, window_height, window_height)),
    panning(false),
    player(player), 
    tile_map(tile_map), 
    tile_palette_view(tile_map, window_height)
{
    house_render_texture.create(window_width, window_height); 
}

HouseScene::~HouseScene() {
}

void HouseScene::Update(const sf::Event& event, const sf::Vector2i current_mouse_position) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
        editor_enabled = !editor_enabled;
        player.Reset();
    }

    if (!editor_enabled) {
        player.Update(event);
        return;
    }

    tile_palette_view.Update(event, current_mouse_position);

    sf::Vector2f current_target_coords = house_render_texture.mapPixelToCoords(
            sf::Vector2i(current_mouse_position.x, current_mouse_position.y)
    );

    current_mouse_grid_position.x = floor(current_target_coords.x / tile_map.SpriteSize());
    current_mouse_grid_position.y = floor(current_target_coords.y / tile_map.SpriteSize());
     
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        
        sf::Vector2f event_target_coords = house_render_texture.mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        
        sf::IntRect pixel_bounds(
            0, 
            0,
            house.bounds.width * tile_map.SpriteSize(),
            house.bounds.height * tile_map.SpriteSize()
        );



        if (pixel_bounds.contains(event_target_coords.x, event_target_coords.y) && 
            !tile_palette_view.GetBackground().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)
        ) {
            auto sprite_size = tile_map.SpriteSize();
            auto found = std::find_if(house.tiles->begin(), house.tiles->end(), [event_target_coords, sprite_size](const auto &t) {
                return sf::FloatRect(
                    t.x * sprite_size, t.y * sprite_size,
                    sprite_size, sprite_size
                ).contains(event_target_coords);
            });
            if (found != house.tiles->end()) {
                house.tiles->erase(found);
            }

            house.tiles->push_back(
                Tile { 
                    (int)event_target_coords.x / tile_map.SpriteSize(),
                    (int)event_target_coords.y / tile_map.SpriteSize(),
                    (int)current_rotation,
                    tile_palette_view.GetSelectedTileIndex()
                }
            );
        }
    }


    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
        house.WriteToFile("./assets/maps/room.bin");
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

    if (panning) {
        auto mouse_delta = current_mouse_position - last_mouse_position;
        house_view.move(mouse_delta.x * -1, mouse_delta.y * -1);
    }

    last_mouse_position = current_mouse_position;

    if (event.type == sf::Event::Resized) {
        house_view.setSize(event.size.width, event.size.height);
        //delete house_render_texture;
        //house_render_texture = new sf::RenderTexture();
        house_render_texture.create(event.size.width, event.size.height); 
    }
 
}

void DrawGrid(sf::RenderTarget &target, int grid_height, int grid_width, int size) {
    int total_grid_height = grid_height * size;
    int total_grid_width = grid_width * size;

    for(auto row = 1; row < (grid_height +1) * size; row = row + size) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, row), sf::Color::White),
            sf::Vertex(sf::Vector2f(total_grid_width, row), sf::Color::White)
        };
        target.draw(line, 2, sf::Lines);
    }

    for(auto col = 1; col < (grid_width + 1) * size; col = col + size) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(col, 0), sf::Color::White),
            sf::Vertex(sf::Vector2f(col, total_grid_height), sf::Color::White)
        };
        target.draw(line, 2, sf::Lines);
    }
}

void HouseScene::Draw(sf::RenderTarget& target) {
    if (!editor_enabled) {
        house_view.setCenter(player.getTransform());
    }

    // Draw Room and Grid
    house_render_texture.setView(house_view);
    house_render_texture.clear();
    house.Draw(house_render_texture, tile_map);

    player.Draw(house_render_texture);

    if (editor_enabled) {
        DrawGrid(
            house_render_texture,
            house.bounds.height, 
            house.bounds.width, 
            tile_map.SpriteSize()
        );

        // Draw Selected Tile
        auto selected_tile_sprite = tile_palette_view.GetSelectedTileSprite();
        selected_tile_sprite.setScale(tile_map.scale, tile_map.scale);
        int half_tile_size = tile_map.SpriteSize() / 2;
        selected_tile_sprite.setPosition(
            (current_mouse_grid_position.x * tile_map.SpriteSize()) + half_tile_size,
            (current_mouse_grid_position.y * tile_map.SpriteSize()) + half_tile_size
        );
        selected_tile_sprite.setColor(sf::Color(255, 255, 255, 170));
        selected_tile_sprite.setOrigin(tile_map.size / 2, tile_map.size / 2);
        selected_tile_sprite.rotate(current_rotation);

        house_render_texture.draw(selected_tile_sprite);
        house_render_texture.display();
    }


    sf::Sprite house_render_sprite(house_render_texture.getTexture());
    target.draw(house_render_sprite);

    if (editor_enabled) {
        //Draw Tile Palette
        tile_palette_view.Draw(target);
    }

}
