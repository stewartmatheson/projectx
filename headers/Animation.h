#pragma once

#include "SpriteSheet.h"

struct AnimationFrame {
    int x;
    int y;
};

class Animation {
    SpriteSheet& sprite_sheet;
    std::vector<AnimationFrame> animation_frames;
    int frame_width;
    int frame_height;
    int current_frame_counter;
    int speed;
public:
    sf::Sprite sprite;
    Animation(SpriteSheet &, std::vector<AnimationFrame>, int, int, int);
    void Update();
};
