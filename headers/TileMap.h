#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

struct TileMap {
	int size;
	int scale;
	sf::Texture* texture;
	std::vector<sf::Sprite>* tiles;

	TileMap(std::string, int, int, int, int);
	~TileMap();

	int tileSize();
};

struct Tile {
    int x;
    int y;
    int rotation;
    int tile_map_index;
};

sf::Sprite CreateTileSprite(int, int, int, int, sf::Texture &, int);
