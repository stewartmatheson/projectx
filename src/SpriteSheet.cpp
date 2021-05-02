#include "SpriteSheet.h"


SpriteSheet::SpriteSheet (std::string texture_path, int scale, int size, int cols, int rows)
	: scale(scale), size(size), texture() {
	if (!texture.loadFromFile(texture_path)) {
		std::cout << "Can't laod file" << std::endl;
		exit(1);
	}

	std::vector<sf::Sprite>* tile_sprites = new std::vector<sf::Sprite>();
	for(int y = 0; y < cols; y++) {
		for(int x = 0; x < rows; x++) {
			tile_sprites->push_back(CreateTileSprite(x, y, scale, size));
		}
	}

	this->tiles = tile_sprites;
};

SpriteSheet::~SpriteSheet() {
	delete tiles;
}

sf::Sprite SpriteSheet::CreateTileSprite(int tile_map_x, int tile_map_y, int scale, int size) {
	sf::Sprite sprite(
		texture,
		sf::IntRect(
			size * tile_map_x, 
			size * tile_map_y, 
			size, 
			size
		)
	);

	sprite.setScale(scale, scale);
	return sprite;
}

int SpriteSheet::SpriteSize() {
  return scale * size;
}
