#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h"

typedef struct {
	sf::RectangleShape* selection_rectangle;	
	sf::RectangleShape* background;	
	std::vector<sf::Sprite>* tiles;
	int offset;
	TileMap* tile_map;
	int selected_tile_index;
} Editor;

Editor* CreateEditor(TileMap &tile_map, int height);
void DestructEditor(Editor& editor);
void DrawEditor(sf::RenderTarget& target, Editor& editor);
void UpdateEditor(Editor& editor, const sf::Event& event);
