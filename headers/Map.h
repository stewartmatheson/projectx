#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "SpriteSheet.h"

// A map holds all data for a given tile layout within the game.
struct Map {
    sf::IntRect bounds;

	std::vector<Tile>* tiles;

	Map(std::string);
	Map(int, int, int, int);
	~Map();

	void Draw(sf::RenderTarget &, const SpriteSheet &) const;
	void WriteToFile(std::string) const;
};

