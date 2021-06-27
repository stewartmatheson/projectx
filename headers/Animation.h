#pragma once

#include "SpriteSheet.h"

struct AnimationFrame {
    int x;
    int y;
};

class Animation {
    std::vector<AnimationFrame> animation_frames;
    std::size_t current_frame_counter;
    int frame_height;
    int frame_width;
    int speed;
    const SpriteSheet &sprite_sheet;

  public:
    sf::Sprite sprite;
    Animation(const SpriteSheet &, std::vector<AnimationFrame>, int, int, int);
    void Update();
};
