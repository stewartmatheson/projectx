#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Editor.h"
#include "Room.h"

int main()
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

    //Room* room = CreateRoom(tile_size, 100, 100);
    
    // TODO : Debug this
    Room room_value = ReadRoomFromFile("./assets/maps/room.bin");
    Room* room = &room_value;


    Editor* editor = CreateEditor(*tile_map, window_height, window_width);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Question : I'm dereferencing here but these functions accept pointers. Is this the right thing to do?
            UpdateEditor(*editor, *room, event);

            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();
        DrawRoom(window, *room, *tile_map);
        DrawEditor(window, *editor, *room);
        window.display();
    }
    return 0;
}
