#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "SpriteSheet.h"
#include "HouseScene.h"

int main(int argc, char** argv)
{
    int window_width = 1000;
    int window_height = 1000;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
    window.setFramerateLimit(60);

    SpriteSheet tile_map(
        "./assets/tilemap.png", 
        4, // Tile scale factor
        16, // Pixel size of tile in tilemap texture
        5,
        7
    );

    SpriteSheet entity_map(
        4, // Tile scale factor
        16
    );

    SpriteSheet player_sprite_sheet(
        "./assets/NightThief.png", 
        4, // Tile scale factor
        320, // Pixel size of tile in tilemap texture
        1,
        1
    );

    std::vector<AnimationFrame> idle_frames;
    for (auto col = 0; col < 10; col++) {
        idle_frames.push_back(AnimationFrame{col, 0});
    }

    std::vector<AnimationFrame> walk_frames;
    for (auto col = 0; col < 10; col++) {
        walk_frames.push_back(AnimationFrame{col, 2});
    }

    std::unordered_map<std::string, Animation> player_animations = {
        {"idle", Animation(player_sprite_sheet, idle_frames, 32, 32, 8) },
        {"walk", Animation(player_sprite_sheet, walk_frames, 32, 32, 8) }
    };
    Entity player = Entity(PlayerEntity, 500.f, .01f, player_animations);
    
    Map map = argc == 2 ? Map(argv[1]) : Map(20, 20, window_height, window_width);
    HouseScene house_scene(tile_map, entity_map, window_height, window_width, map, player);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            house_scene.Update(event, sf::Mouse::getPosition(window));
         
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

        }

        window.clear();
        house_scene.Draw(window);

        window.display();
    }
    return 0;
}
