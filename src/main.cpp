#include <SFML/Graphics.hpp>
#include <iostream>

void draw_grid_to_render_target(sf::RenderTarget &target, int height, int width, int size, int scale) {
	for(int row = 0; row < height / (size * scale); row++) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(0, row * (size * scale)), sf::Color::White),
			sf::Vertex(sf::Vector2f(width, row * (size * scale)), sf::Color::White)
		};
		target.draw(line, 2, sf::Lines);
	}

	for(int col = 0; col < width / size; col++) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(col * (size * scale), 0), sf::Color::White),
			sf::Vertex(sf::Vector2f(col * (size * scale), height), sf::Color::White)
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

	std::vector<sf::Sprite> tiles;

	for(int y = 0; y < tile_cols; y++) {
		for(int x = 0; x < tile_rows; x++) {
			sf::Sprite sprite = sf::Sprite();
			sprite.setTextureRect(sf::IntRect(tile_size * x, tile_size * y, tile_size, tile_size));
			sprite.setTexture(texture);
			sprite.setScale(scale, scale);
			tiles.push_back(sprite);
		}
	}

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(tile_size * scale, tile_size * scale));
	rectangle.setOutlineColor(sf::Color::Blue);
	rectangle.setOutlineThickness(2);
	rectangle.setFillColor(sf::Color::Transparent);

    while (window.isOpen())
    {

		for(int i = 0; i < tiles.size(); i++) {
			int current_y_pos = 
				(i * scale * tile_size) + 
				(offset * i) + offset;

			tiles[i].setPosition(offset, current_y_pos);
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
					int current_event_tile_index = 0;
					for(sf::Sprite t : tiles) {
						if(t.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							selected_tile_index = current_event_tile_index;		
						}
						current_event_tile_index++;
					}
				}
			}
        }

        window.clear();
		left_toolbar_render_texture.clear();
		grid_render_texture.clear();

		draw_grid_to_render_target(grid_render_texture, window_height , window_width, tile_size, scale);

		left_toolbar_render_texture.draw(left_toolbar_background_shape);

		for(sf::Sprite t : tiles) {
			left_toolbar_render_texture.draw(t);
		}
		left_toolbar_render_texture.draw(rectangle);
		left_toolbar_render_texture.display();


		const sf::Texture& grid_texture = grid_render_texture.getTexture();
		sf::Sprite grid_render_sprite(grid_texture);
		window.draw(grid_render_sprite);

		const sf::Texture& left_toolbar_texture = left_toolbar_render_texture.getTexture();
		sf::Sprite left_toolbar_render_sprite(left_toolbar_texture);
		window.draw(left_toolbar_render_sprite);

        window.display();
    }

    return 0;
}
