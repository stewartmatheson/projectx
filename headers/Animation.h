#pragma once

#include <memory>

#include "SpriteSheet.h"
#include "Screen.h"

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
    const std::shared_ptr<SpriteSheet> sprite_sheet;

  public:
    sf::Sprite sprite;
    Animation(const std::shared_ptr<SpriteSheet>, std::vector<AnimationFrame>, int, int, int);
    void Update();
};
