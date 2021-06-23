#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class SpriteSheet {
    sf::Sprite CreateTileSprite(int, int, int, int);
	std::vector<sf::Sprite> sprites;
	int scale;
	int size;
	sf::Texture texture;
    sf::RenderTexture icon_sprite_render_texture;
public:
    void CreateIconSprite(sf::Color, int);
	SpriteSheet(std::string, int, int, int, int);
	SpriteSheet(int, int);
	const int GetSpriteSize() const;
    const std::vector<sf::Sprite>& GetSprites() const;
    const sf::Texture& GetTexture() const;
    const int GetScale() const;
    const int GetSize() const;
};

