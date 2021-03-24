#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Editor.h"

int main()
{
	int window_width = 800;
	int window_height = 600;
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
	TileMap* tile_map = CreateTileMap(
			"../assets/tilemap.png", 
			4, // Tile scale factor
			16, // Pixel size of tile in tilemap texture
			5,
			7
			);

	Editor* editor = CreateEditor(*tile_map, window_height);
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			UpdateEditor(*editor, event);

			if (event.type == sf::Event::Closed)
				window.close();


			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		}

		window.clear();
		DrawEditor(window, *editor);
		window.display();
	}
	return 0;
}
