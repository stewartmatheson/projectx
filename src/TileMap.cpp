#include "TileMap.h"

sf::Sprite CreateTileSprite(int tile_map_x, int tile_map_y, int scale, int size, sf::Texture& texture) {
	sf::Sprite sprite;
	sprite.setTextureRect(
		sf::IntRect(
			size * tile_map_x, 
			size * tile_map_y, 
			size, 
			size
		)
	);

	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	return sprite;
}

TileMap::TileMap (std::string texture_path, int scale, int size, int cols, int rows) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(texture_path)) {
		std::cout << "Can't laod file" << std::endl;
		exit(1);
	}

	std::vector<sf::Sprite>* tile_sprites = new std::vector<sf::Sprite>();
	for(int y = 0; y < cols; y++) {
		for(int x = 0; x < rows; x++) {
			tile_sprites->push_back(CreateTileSprite(x, y, scale, size, *texture));
		}
	}

	this->size = size;
	this->scale = scale;
	this->texture = texture;
	this->tiles = tile_sprites;
};

TileMap::~TileMap() {
	delete texture;
}

int TileMap::tileSize() {
  return scale * size;
}
