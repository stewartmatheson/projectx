#include "Tile.h"

sf::Sprite CreateTileSprite(int tile_map_x, int tile_map_y, int scale, int size, sf::Texture* texture) {
	sf::Sprite sprite = sf::Sprite();
	sprite.setTextureRect(
		sf::IntRect(
			size * tile_map_x, 
			size * tile_map_y, 
			size, 
			size
		)
	);

	sprite.setTexture(*texture);
	sprite.setScale(scale, scale);
	return sprite;
}

TileMap CreateTileMap (std::string texture_path, int scale, int size, int cols, int rows) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile("../assets/tilemap.png")) {
		std::cout << "Can't laod file" << std::endl;
		exit(1);
	}

	std::vector<sf::Sprite> tile_sprites;
	for(int y = 0; y < cols; y++) {
		for(int x = 0; x < rows; x++) {
			tile_sprites.push_back(CreateTileSprite(x, y, scale, size, texture));
		}
	}

	return { size, scale, texture, tile_sprites };
};

void DestructTileMap(TileMap &tile_map) {
	delete tile_map.texture;
}
