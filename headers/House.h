#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "SpriteSheet.h"

// A map holds all data for a given tile layout within the game.
struct House {
    sf::IntRect bounds;

	std::vector<Tile>* tiles;

	House(std::string);
	House(int, int, int, int);
	~House();

	void Draw(sf::RenderTarget &, SpriteSheet &) const;
	void WriteToFile(std::string) const;
};

