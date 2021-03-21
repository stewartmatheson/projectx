#include "Editor.h"

Editor* CreateEditor(TileMap &tile_map, int height) {
	int offset = 20;
	int left_toolbar_width = offset * 2 + (tile_map.scale * tile_map.size);

	sf::RectangleShape* selection = new sf::RectangleShape();
	selection->setSize(
		sf::Vector2f(
			tile_map.size * tile_map.scale, 
			tile_map.size * tile_map.scale
		)
	);
	selection->setOutlineColor(sf::Color::Blue);
	selection->setOutlineThickness(2);
	selection->setFillColor(sf::Color::Transparent);

	sf::RectangleShape* background = new sf::RectangleShape(sf::Vector2f(left_toolbar_width, height));
	background->setFillColor(sf::Color(60,60,60, 255));

	Editor* editor = (Editor*)malloc(sizeof(*editor));
	editor->selection_rectangle = selection;
	editor->background = background;
	editor->tiles = tile_map.tiles;

	// TODO : We might need to copy here. Not sure 
	editor->tile_map = &tile_map;

	editor->offset = offset;
	editor->selected_tile_index = 0;
	return editor;
}

void DestructEditor(Editor &editor) {
	delete editor.selection_rectangle;
	delete editor.background;
	free(&editor);
}

void UpdateEditor(Editor& editor, sf::Event& event) {
	for(int i = 0; i < editor.tiles.size(); i ++) {
		int current_y_pos = 
			(i * editor.tile_map->scale * editor.tile_map->size) + 
			(editor.offset * i) + editor.offset;
		editor.tiles[i].setPosition(editor.offset, current_y_pos);
	}

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			int current_event_tile_index = 0;
			for(sf::Sprite t : editor.tiles) {
				if(t.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					editor.selected_tile_index = current_event_tile_index;		
				}
				current_event_tile_index++;
			}
		}
	}
}

void DrawEditor(sf::RenderTarget& target, Editor& editor) {
	for(sf::Sprite tile_sprite : editor.tiles) {
		target.draw(tile_sprite);
	}
	target.draw(*editor.background);
	target.draw(*editor.selection_rectangle);
}
