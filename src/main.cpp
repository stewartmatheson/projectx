#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Editor.h"
#include "Map.h"

int main()
{
    int window_width = 800;
    int window_height = 600;
    int tile_size = 16;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
    TileMap* tile_map = CreateTileMap(
            "../assets/tilemap.png", 
            4, // Tile scale factor
            tile_size, // Pixel size of tile in tilemap texture
            5,
            7
            );

    Map* map = CreateMap(tile_size, 100, 100);
    Editor* editor = CreateEditor(*tile_map, window_height);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            UpdateEditor(*editor, *map, event);

            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();
        DrawMap(window, *map);
        DrawEditor(window, *editor, *map);
        window.display();
    }
    return 0;
}
