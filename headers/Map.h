#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "SpriteSheet.h"

struct MapTile {
    int x;
    int y;
    int rotation;
    int tile_map_index;
};

struct TileLayer {
    int layer_index;
    std::vector<MapTile> tiles;
};

// A map holds all data for a given tile layout within the game.
class Map {
    int map_file_version;
    sf::IntRect bounds;
    std::vector<TileLayer> tile_layers;
    std::vector<Entity> entities;

public:
	Map(std::string);
	Map(int, int, int, int);

	void WriteToFile(std::string) const;
    const sf::IntRect GetBounds() const;
    const std::vector<TileLayer>& GetTileLayers() const;
    const std::vector<Entity>& GetEntities() const;
    void AddTile(int, MapTile);
    void AddEntity(Entity);
};

