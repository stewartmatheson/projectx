#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "Editor.h"


void draw_grid_to_render_target(sf::RenderTarget &target, int grid_height, int grid_width, int size) {
	int total_grid_height = grid_height * size;
	int total_grid_width = grid_width * size;

	for(int row = 1; row < grid_height * size; row = row + size) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(0, row), sf::Color::White),
			sf::Vertex(sf::Vector2f(total_grid_width, row), sf::Color::White)
		};
		target.draw(line, 2, sf::Lines);
	}

	for(int col = 1; col < grid_width * size; col = col + size) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(col, 0), sf::Color::White),
			sf::Vertex(sf::Vector2f(col, total_grid_height), sf::Color::White)
		};
		target.draw(line, 2, sf::Lines);
	}
}

int main()
{
	// int scale = 4;
	// int offset = 20;
	int window_width = 800;
	int window_height = 600;
	// int selected_tile_index = 0;
	int grid_height = 100;
	int grid_width = 100;

	// int tile_cols = 5;
	// int tile_rows = 7;
	//int tile_size = 16;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
	sf::RenderTexture grid_render_texture;

	grid_render_texture.create(window_width, window_height);

	/*
	sf::Texture texture;
	if (!texture.loadFromFile("../assets/tilemap.png")) {
		std::cout << "Can't laod file" << std::endl;
		return 0;
	}
	*/
	TileMap* tile_map = CreateTileMap(
		"../assets/tilemap.png", 
		4, // Tile scale factor
		16 // Pixel size of tile in tilemap texture
	);

	Editor* editor = CreateEditor();

	// std::vector<sf::Sprite> toolbar_tiles;

	/*
	for(int y = 0; y < tile_cols; y++) {
		for(int x = 0; x < tile_rows; x++) {
			sf::Sprite sprite = sf::Sprite();
			sprite.setTextureRect(sf::IntRect(tile_size * x, tile_size * y, tile_size, tile_size));
			sprite.setTexture(texture);
			sprite.setScale(scale, scale);
			toolbar_tiles.push_back(sprite);
		}
	}


	std::vector<sf::IntRect> grid_tiles;
	for(int x = 1; x < grid_height * (tile_size * scale); x = x + (tile_size * scale)) {
		for(int y = 1; y < grid_width * (tile_size * scale); y = y + (tile_size * scale)) {
			grid_tiles.push_back(sf::IntRect(left_toolbar_width + x, y, tile_size * scale, tile_size * scale));
		}
	}

	*/

	std::vector<sf::Sprite> sprite_tiles;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
			UpdateEditor(editor);

            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {

					// grid tiles. This should move to a map abstraction
					int current_grid_tile_index = 0;
					for(sf::IntRect r : grid_tiles) {
						if(r.contains(event.mouseButton.x, event.mouseButton.y)) {
							sf::Sprite new_sprite(toolbar_tiles[selected_tile_index]);
							new_sprite.setPosition(r.left, r.top);
							sprite_tiles.push_back(new_sprite);
						}
						current_grid_tile_index++;
					}
				}
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
        }

        window.clear();
		grid_render_texture.clear();

		draw_grid_to_render_target(grid_render_texture, grid_height, grid_width, tile_size * scale);

		grid_render_texture.display();	

		const sf::Texture& grid_texture = grid_render_texture.getTexture();
		sf::Sprite grid_render_sprite(grid_texture);
		grid_render_sprite.setPosition(left_toolbar_width, 0);
		
		window.draw(grid_render_sprite);

		DrawEditor(window, &editor);

		for(sf::Sprite sprite : sprite_tiles) {
			window.draw(sprite);
		}

        window.display();
    }

    return 0;
}
