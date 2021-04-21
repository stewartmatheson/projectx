#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Editor.h"

int main(int argc, char** argv)
{
    const bool ENABLE_EDITOR = true;
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
    
    Room* room;
    
    if (argc == 2) {
        room = ReadRoomFromFile(argv[1]);
    } else {
        room = new Room(30, 30, window_height, window_width);
    }

    Editor editor(tile_map, window_height, window_width);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (ENABLE_EDITOR) {
                UpdateEditor(editor, event, *room, sf::Mouse::getPosition(window));
            } 
         
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();

        if (ENABLE_EDITOR) {
            DrawEditor(window, editor, *room);
        } else {
            DrawRoom(window, *room, tile_map);
        }
        window.display();
    }
    return 0;
}
