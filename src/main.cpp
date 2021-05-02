#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "SpriteSheet.h"
#include "RoomScene.h"

int main(int argc, char** argv)
{
    int window_width = 1400;
    int window_height = 1400;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");

    SpriteSheet tile_map(
        "./assets/tilemap.png", 
        4, // Tile scale factor
        16, // Pixel size of tile in tilemap texture
        5,
        7
    );

    SpriteSheet player_sprite_sheet(
        "./assets/NightThief.png", 
        4, // Tile scale factor
        320, // Pixel size of tile in tilemap texture
        1,
        1
    );

    std::vector<AnimationFrame> idle_frames;
    for (int col = 0; col < 10; col++) {
        idle_frames.push_back(AnimationFrame{col, 0});
    }
    std::unordered_map<std::string, Animation> player_animations = {
        {"idle", Animation(player_sprite_sheet, idle_frames, 32, 32, 160) }
    };
    Entity player = Entity(15.f, .01f, player_animations);
    
    Room room = argc == 2 ? Room(argv[1]) : Room(20, 20, window_height, window_width);
    RoomScene room_scene(tile_map, window_height, window_width, room, player);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                std::cout << event.size.width << std::endl;
                window.setView(sf::View(visibleArea));
            }

            room_scene.Update(event, sf::Mouse::getPosition(window));
         
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

        }

        window.clear();
        room_scene.Draw(window);

        window.display();
    }
    return 0;
}
