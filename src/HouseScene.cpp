#include <math.h>
#include <fstream>
#include "HouseScene.h"

HouseScene::HouseScene(
        SpriteSheet &tile_map, 
        SpriteSheet &entity_map, 
        int window_height, 
        int window_width, 
        Map &map, 
        Entity &player
) : current_rotation(0), 
    editor_enabled(true), 
    map(map), 
    house_view(sf::FloatRect(0, 0, window_width, window_height)),
    panning(false),
    player(player), 
    tile_map(tile_map), 
    entity_map(entity_map), 
    tile_palette_view(tile_map, entity_map, window_height),
    current_selected_tile_layer(0)
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

    current_mouse_grid_position.x = floor(current_target_coords.x / tile_map.GetSpriteSize());
    current_mouse_grid_position.y = floor(current_target_coords.y / tile_map.GetSpriteSize());
     
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        
        sf::Vector2f event_target_coords = house_render_texture.mapPixelToCoords(
            sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
        );
        
        sf::IntRect pixel_bounds(
            0, 
            0,
            map.GetBounds().width * tile_map.GetSpriteSize(),
            map.GetBounds().height * tile_map.GetSpriteSize()
        );

        if (pixel_bounds.contains(event_target_coords.x, event_target_coords.y) && 
            !tile_palette_view.GetBackground().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)
        ) {
            auto x = (int)event_target_coords.x / tile_map.GetSpriteSize();
            auto y = (int)event_target_coords.y / tile_map.GetSpriteSize();

            if (tile_palette_view.GetSelectedTile().type == PaletteTile) {
                map.AddTile(
                    current_selected_tile_layer, 
                    MapTile { 
                        x,
                        y,
                        (int)current_rotation,
                        tile_palette_view.GetSelectedTileIndex()
                    }
                );
            } else if (tile_palette_view.GetSelectedTile().type == PaletteEntity){
                map.AddEntity(Entity(tile_palette_view.GetSelectedTile().entity_type, 0, 0, x, y));
            } else {
                std::cout << "Map type not supported" << std::endl;
                exit(1);
            }
        }
    }


    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
        map.WriteToFile("./assets/maps/room.bin");
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
        house_view.setCenter(player.GetTransform());
    }

    // Draw Room and Grid
    house_render_texture.setView(house_view);
    house_render_texture.clear();

    for(const auto &tile_layer : map.GetTileLayers()) {
        for(const auto &tile : tile_layer.tiles) {
            sf::Sprite sprite_to_draw(tile_map.GetSprites()[tile.tile_map_index]);
            sprite_to_draw.setRotation(tile.rotation);
            int half_tile_size = tile_map.GetSpriteSize() / 2;
            sprite_to_draw.setPosition(
                (tile.x * tile_map.GetSpriteSize()) + half_tile_size,
                (tile.y * tile_map.GetSpriteSize()) + half_tile_size
            );
            sprite_to_draw.setOrigin(tile_map.GetSize() / 2, tile_map.GetSize() / 2);
            house_render_texture.draw(sprite_to_draw);
        }
    }

    auto entities = map.GetEntities();
    std::for_each(entities.begin(), entities.end(), [this](const auto &entity){
        sf::Sprite sprite_to_draw(entity_map.GetSprites()[entity.GetTileMapIndex()]);
        sprite_to_draw.setRotation(entity.GetRotation());
        int half_tile_size = entity_map.GetSpriteSize() / 2;
        sprite_to_draw.setPosition(
            (entity.GetTransform().x * entity_map.GetSpriteSize()) + half_tile_size,
            (entity.GetTransform().y * entity_map.GetSpriteSize()) + half_tile_size
        );
        sprite_to_draw.setOrigin(entity_map.GetSize() / 2, entity_map.GetSize() / 2);
        house_render_texture.draw(sprite_to_draw);
    });

    player.Draw(house_render_texture);

    if (editor_enabled) {
        DrawGrid(
            house_render_texture,
            map.GetBounds().height, 
            map.GetBounds().width, 
            tile_map.GetSpriteSize()
        );

        // Draw Selected Tile
        auto selected_tile_sprite = tile_palette_view.GetSelectedTile().icon;
        int half_tile_size = tile_map.GetSpriteSize() / 2;
        selected_tile_sprite.setPosition(
            (current_mouse_grid_position.x * tile_map.GetSpriteSize()) + half_tile_size,
            (current_mouse_grid_position.y * tile_map.GetSpriteSize()) + half_tile_size
        );
        selected_tile_sprite.setColor(sf::Color(255, 255, 255, 170));
        selected_tile_sprite.setOrigin(tile_map.GetSize() / 2, tile_map.GetSize() / 2);
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
