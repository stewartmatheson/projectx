#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "RoomScene.h"

int main(int argc, char** argv)
{
    int window_width = 1400;
    int window_height = 1400;
    int tile_size = 16;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
    TileMap tile_map(
            "./assets/tilemap.png", 
            4, // Tile scale factor
            tile_size, // Pixel size of tile in tilemap texture
            5,
            7
            );
    
    Room room = argc == 2 ? Room(argv[1]) : Room(20, 20, window_height, window_width);

    RoomScene room_scene(tile_map, window_height, window_width, room);


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
