#include "Map.h"
#include <math.h>

Map* CreateMap(int tile_size, int map_height, int map_width) {
	Map* map = (Map*)malloc(sizeof(*map));
    map->bounds = sf::IntRect(0, 0, tile_size * map_width, tile_size * map_height);
    map->tiles = new std::vector<sf::Sprite>();
    return map;
}

void DestructMap(Map& map) { }

void DrawMap(sf::RenderTarget& target, Map& map) {
	for(sf::Sprite map_tile : *map.tiles) {
		target.draw(map_tile);
	}
}

sf::Vector2i GetTilePositionAt(Map& map, int x, int y, int tile_map_size) {
    if (map.bounds.contains(x,y)) {
        return sf::Vector2i(floor(x / tile_map_size), floor(y / tile_map_size));
    } else {
        return sf::Vector2i();
    }
}
