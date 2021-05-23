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
    sf::Sprite CreateIconSprite(sf::Color, int);
public:
	SpriteSheet(std::string, int, int, int, int);
	SpriteSheet(int, int);
	int GetSpriteSize() const;
    std::vector<sf::Sprite> GetSprites();
    const sf::Texture& GetTexture();
    int GetScale() const;
    int GetSize() const;
    
};

