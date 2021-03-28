#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Map.h"

/**
 * An editor contains all data required to add, remove and edit tiles on a given map
 */
typedef struct {
	sf::RectangleShape* selection_rectangle;	

    // The background shape for the tile toolbar editor
	sf::RectangleShape* background;	

    // A list of vector of spirte tiles for rendering in the sidebar of the editor
	std::vector<sf::Sprite>* tiles;

	int offset;
	TileMap* tile_map;

    // The currently selected tile index. This is the index for the tiles vector
	int selected_tile_index;
} Editor;

Editor* CreateEditor(TileMap &tile_map, int height);

void DestructEditor(Editor& editor);

void DrawEditor(sf::RenderTarget& target, Editor& editor, const Map& map);

void UpdateEditor(
    Editor& editor, 
    Map& map,
    const sf::Event& event
);
