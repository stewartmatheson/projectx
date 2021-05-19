#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Entity.h"
#include "SpriteSheet.h"

struct TileLayer {
    int layer_index;
	std::vector<Tile> tiles;
};

// A map holds all data for a given tile layout within the game.
class Map {
    int map_file_version;
    sf::IntRect bounds;
    std::vector<TileLayer> tile_layers;
    std::vector<Entity> entites;
public:
	Map(std::string);
	Map(int, int, int, int, int);

	void WriteToFile(std::string);
    sf::IntRect GetBounds();
    std::vector<TileLayer> GetTileLayers();
};

