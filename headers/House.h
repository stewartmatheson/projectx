#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "SpriteSheet.h"

// A map holds all data for a given tile layout within the game.
struct House {
    sf::IntRect bounds;
	// std::vector<sf::Sprite>* tiles;
	std::vector<Tile>* tiles;

	/**
	 * @brief 
	 *
	 * @param int window_height
	 * @param int window_width
	 * @param int map_height
	 * @param int map_width
	 *
	 * @return The created room
	 */
	House(std::string);
	House(int, int, int, int);
	~House();

	void Draw(sf::RenderTarget &, SpriteSheet &);

	void WriteToFile(std::string);
};

