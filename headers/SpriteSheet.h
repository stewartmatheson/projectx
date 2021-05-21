#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class SpriteSheet {
    sf::Sprite CreateTileSprite(int, int, int, int);

public:
	int scale;
	int size;
	sf::Texture texture;
	std::vector<sf::Sprite>* tiles;
	SpriteSheet(std::string, int, int, int, int);
	~SpriteSheet();
	int SpriteSize() const;
};

