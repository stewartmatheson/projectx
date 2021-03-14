#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	int scale = 4;
	int offset = 10;
	int selected_tile_index = 0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	sf::Texture texture;
	if (!texture.loadFromFile("../assets/tilemap.png")) {
		std::cout << "Can't laod file" << std::endl;
		return 0;
	}


	std::vector<sf::Sprite> tiles;

	int cols = 5;
	int rows = 7;
	int size = 16;
	for(int y = 0; y < cols; y++) {
		for(int x = 0; x < rows; x++) {
			sf::Sprite sprite = sf::Sprite();
			sprite.setTextureRect(sf::IntRect(size * x, size * y, size, size));
			sprite.setTexture(texture);
			sprite.setScale(scale, scale);
			tiles.push_back(sprite);
		}
	}

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(size * scale, size * scale));
	rectangle.setOutlineColor(sf::Color::Blue);
	rectangle.setOutlineThickness(2);
	rectangle.setFillColor(sf::Color::Transparent);

    while (window.isOpen())
    {

		for(int i = 0; i < tiles.size(); i++) {
			int current_x_pos = 
				(i * scale * size) + 
				(offset * i);

			tiles[i].setPosition(current_x_pos, 10);
			if (selected_tile_index == i) {
				rectangle.setPosition(current_x_pos, 10);
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
							std::cout << "Changed Index" << std::endl;
						}
						current_event_tile_index++;
					}
				}
			}
        }

        window.clear();

		for(sf::Sprite t : tiles) {
			window.draw(t);
		}
		window.draw(rectangle);
        window.display();
    }

    return 0;
}
