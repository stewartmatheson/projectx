#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class TileMap {
	sf::Texture* texture;

public:
	int size;
	int scale;
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
