#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Room.h"

int main(int argc, char** argv)
{
    int window_width = 1800;
    int window_height = 1400;
    int tile_size = 16;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
    TileMap* tile_map = CreateTileMap(
            "../assets/tilemap.png", 
            4, // Tile scale factor
            tile_size, // Pixel size of tile in tilemap texture
            5,
            7
            );


    Editor* editor = CreateEditor(*tile_map, window_height, window_width);
    
    Room* room;
    
    if (argc == 2) {
        room = ReadRoomFromFile(argv[1]);
    } else {
        room = CreateRoom(tile_size, 100, 100);
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Question : I'm dereferencing here but these functions accept pointers. Is this the right thing to do?
            UpdateRoom(*room, event, *editor);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();
        DrawRoom(window, *room, *tile_map, *editor);
        window.display();
    }
    return 0;
}
