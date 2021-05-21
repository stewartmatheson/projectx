#include "SpriteSheet.h"


SpriteSheet::SpriteSheet (std::string texture_path, int scale, int size, int cols, int rows)
	: scale(scale), size(size), texture() {
	if (!texture.loadFromFile(texture_path)) {
		std::cout << "Can't laod file" << std::endl;
		exit(1);
	}

	tiles = new std::vector<sf::Sprite>();
	for(auto y = 0; y < cols; y++) {
		for(auto x = 0; x < rows; x++) {
			tiles->push_back(CreateTileSprite(x, y, scale, size));
		}
	}
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

int SpriteSheet::SpriteSize() const {
  return scale * size;
}
