#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class SpriteSheet {
    sf::Sprite CreateTileSprite(int, int, int, int);

public:
	sf::Texture texture;
	int size;
	int scale;
	std::vector<sf::Sprite>* tiles;
	SpriteSheet(std::string, int, int, int, int);
	~SpriteSheet();
	int SpriteSize();
};

