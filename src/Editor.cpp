#include "Editor.h"

void draw_grid_to_render_target(sf::RenderTarget &target, int grid_height, int grid_width, int size) {
	int total_grid_height = grid_height * size;
	int total_grid_width = grid_width * size;

	for(int row = 1; row < grid_height * size; row = row + size) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(0, row), sf::Color::White),
			sf::Vertex(sf::Vector2f(total_grid_width, row), sf::Color::White)
		};
		target.draw(line, 2, sf::Lines);
	}

	for(int col = 1; col < grid_width * size; col = col + size) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(col, 0), sf::Color::White),
			sf::Vertex(sf::Vector2f(col, total_grid_height), sf::Color::White)
		};
		target.draw(line, 2, sf::Lines);
	}
}

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

	std::vector<sf::IntRect> grid_tiles;
	for(int x = 1; x < grid_height * (tile_size * scale); x = x + (tile_size * scale)) {
		for(int y = 1; y < grid_width * (tile_size * scale); y = y + (tile_size * scale)) {
			grid_tiles.push_back(sf::IntRect(left_toolbar_width + x, y, tile_size * scale, tile_size * scale));
		}
	}

	Editor* editor = (Editor*)malloc(sizeof(*editor));
	editor->selection_rectangle = selection;
	editor->background = background;
	editor->tiles = new std::vector<sf::Sprite>(*tile_map.tiles);

	// TODO : We might need to copy here. Not sure 
	editor->tile_map = &tile_map;

	editor->offset = offset;
	editor->selected_tile_index = 0;
	return editor;
}

void DestructEditor(Editor& editor) {
	delete editor.selection_rectangle;
	delete editor.background;
    delete editor.tiles;
	free(&editor);
}

void UpdateEditor(Editor& editor, const sf::Event& event) {
    editor.selection_rectangle->setPosition((*editor.tiles)[editor.selected_tile_index].getPosition());
	for(int i = 0; i < editor.tiles->size(); i ++) {
		int current_y_pos = 
			(i * editor.tile_map->scale * editor.tile_map->size) + 
			(editor.offset * i) + editor.offset;
		(*editor.tiles)[i].setPosition(editor.offset, current_y_pos);
	}

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			int current_event_tile_index = 0;
			for(sf::Sprite t : *editor.tiles) {
				if(t.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					editor.selected_tile_index = current_event_tile_index;		
				}
				current_event_tile_index++;
			}
		}
	}

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {

			// grid tiles. This should move to a map abstraction
			int current_grid_tile_index = 0;
			for(sf::IntRect r : grid_tiles) {
				if(r.contains(event.mouseButton.x, event.mouseButton.y)) {
					sf::Sprite new_sprite(editor.toolbar_tiles[selected_tile_index]);
					new_sprite.setPosition(r.left, r.top);
					sprite_tiles.push_back(new_sprite);
				}
				current_grid_tile_index++;
			}
		}
	}

}

void DrawEditor(sf::RenderTarget& target, Editor& editor) {
	draw_grid_to_render_target(target, 100, 100, editor.tile_map->size * editor.tile_map->scale);
	target.draw(*editor.background);
	for(sf::Sprite tile_sprite : *editor.tiles) {
		target.draw(tile_sprite);
	}
	target.draw(*editor.selection_rectangle);
}

