#include <SFML/Graphics.hpp>
#include <iostream>

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
	int scale = 4;
	int offset = 20;
	int window_width = 800;
	int window_height = 600;
	int selected_tile_index = 0;
	int grid_height = 100;
	int grid_width = 100;

	int tile_cols = 5;
	int tile_rows = 7;
	int tile_size = 16;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
	sf::RenderTexture left_toolbar_render_texture;
	sf::RenderTexture grid_render_texture;

	int left_toolbar_width = offset * 2 + (scale * tile_size);
	left_toolbar_render_texture.create(left_toolbar_width, window_height);
	grid_render_texture.create(window_width, window_height);
	sf::RectangleShape left_toolbar_background_shape(sf::Vector2f(left_toolbar_width, window_height));
	left_toolbar_background_shape.setFillColor(sf::Color(60,60,60, 255));

	sf::Texture texture;
	if (!texture.loadFromFile("../assets/tilemap.png")) {
		std::cout << "Can't laod file" << std::endl;
		return 0;
	}

	std::vector<sf::Sprite> toolbar_tiles;

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

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(tile_size * scale, tile_size * scale));
	rectangle.setOutlineColor(sf::Color::Blue);
	rectangle.setOutlineThickness(2);
	rectangle.setFillColor(sf::Color::Transparent);


	std::vector<sf::Sprite> sprite_tiles;

    while (window.isOpen())
    {

		for(int i = 0; i < toolbar_tiles.size(); i++) {
			int current_y_pos = 
				(i * scale * tile_size) + 
				(offset * i) + offset;

			toolbar_tiles[i].setPosition(offset, current_y_pos);
			if (selected_tile_index == i) {
				rectangle.setPosition(offset, current_y_pos);
			}
		}

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					// tiles for left toolbar
					int current_event_tile_index = 0;
					for(sf::Sprite t : toolbar_tiles) {
						if(t.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							selected_tile_index = current_event_tile_index;		
						}
						current_event_tile_index++;
					}

					
					// grid tiles
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
		left_toolbar_render_texture.clear();
		grid_render_texture.clear();

		draw_grid_to_render_target(grid_render_texture, grid_height, grid_width, tile_size * scale);



		left_toolbar_render_texture.draw(left_toolbar_background_shape);

		for(sf::Sprite t : toolbar_tiles) {
			left_toolbar_render_texture.draw(t);
		}
		left_toolbar_render_texture.draw(rectangle);
		left_toolbar_render_texture.display();

		grid_render_texture.display();	

		const sf::Texture& grid_texture = grid_render_texture.getTexture();
		sf::Sprite grid_render_sprite(grid_texture);
		grid_render_sprite.setPosition(left_toolbar_width, 0);
		
		window.draw(grid_render_sprite);

		const sf::Texture& left_toolbar_texture = left_toolbar_render_texture.getTexture();
		sf::Sprite left_toolbar_render_sprite(left_toolbar_texture);
		window.draw(left_toolbar_render_sprite);

		for(sf::Sprite sprite : sprite_tiles) {
			window.draw(sprite);
		}

        window.display();
    }

    return 0;
}
