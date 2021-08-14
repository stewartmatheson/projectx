#include "SpriteSheet.h"

// For now we will assume that this is a constructor for a sprite sheet from a
// texture file
SpriteSheet::SpriteSheet(std::string texture_path, int scale, int size,
                         int cols, int rows)
    : texture_path(texture_path), sprites(), scale(scale), size(size), texture() {

    LoadFromFile();
    for (auto y = 0; y < cols; y++) {
        for (auto x = 0; x < rows; x++) {
            sprites.push_back(CreateTileSprite(x, y, scale, size));
        }
    }
};

// For now we will assume that this is a entity sprite sheet drawn with code
SpriteSheet::SpriteSheet(int scale, int size)
    : sprites(), scale(scale), size(size), texture() {
    // TODO : This will never allow us to create more than two sprites
    icon_sprite_render_texture.create(size * 2, size);
};

void SpriteSheet::CreateIconSprite(sf::Color color, int render_offset) {
    auto icon_rect = sf::RectangleShape(sf::Vector2f(size, size));
    icon_rect.setFillColor(color);
    icon_rect.setPosition(size * render_offset, 0);
    icon_sprite_render_texture.draw(icon_rect);
    icon_sprite_render_texture.display();

    auto sprite = sf::Sprite(icon_sprite_render_texture.getTexture(),
                             sf::IntRect(size * render_offset, 0, size, size));
    sprite.setScale(scale, scale);
    sprites.push_back(sprite);
}

sf::Sprite SpriteSheet::CreateTileSprite(int tile_map_x, int tile_map_y,
                                         int scale, int size) {
    sf::Sprite sprite(
        texture, sf::IntRect(size * tile_map_x, size * tile_map_y, size, size));

    sprite.setScale(scale, scale);
    return sprite;
}

const int SpriteSheet::GetSpriteSize() const { return scale * size; }

const int SpriteSheet::GetScale() const { return scale; }

const int SpriteSheet::GetSize() const { return size; }

const sf::Texture &SpriteSheet::GetTexture() const { return texture; }

const std::vector<sf::Sprite> &SpriteSheet::GetSprites() const {
    return sprites;
}

void SpriteSheet::LoadFromFile() {
    // Some textures may not have a file. This is a noop
    if (texture_path == "") {
        return;
    }

    if (!texture.loadFromFile(texture_path)) {
        std::cout << "Can't laod file" << std::endl;
        exit(1);
    }
}

void SpriteSheet::Reload() {
    LoadFromFile();
}
