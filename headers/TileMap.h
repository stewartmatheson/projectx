#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

struct TileMap {
	int size;
	int scale;
	sf::Texture* texture;
	std::vector<sf::Sprite>* tiles;
};

struct Tile {
    int x;
    int y;
    int rotation;
    int tile_map_index;
};

TileMap *CreateTileMap(std::string, int, int, int, int);
void DestructTileMap(TileMap &);
sf::Sprite CreateTileSprite(int, int, int, int, sf::Texture &, int);
