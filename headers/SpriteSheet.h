#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class SpriteSheet {
    std::string texture_path;
    sf::Sprite CreateTileSprite(int, int, int, int);
    std::vector<sf::Sprite> sprites;
    int scale;
    int size;
    sf::Texture texture;
    sf::RenderTexture icon_sprite_render_texture;
    void LoadFromFile();

  public:
    SpriteSheet(std::string, int, int, int, int);
    SpriteSheet(int, int);
    void CreateIconSprite(sf::Color, int);
    const int GetSpriteSize() const;
    const std::vector<sf::Sprite> &GetSprites() const;
    const sf::Texture &GetTexture() const;
    const int GetScale() const;
    const int GetSize() const;
    void Reload();
};
