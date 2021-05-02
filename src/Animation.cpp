#include "Animation.h"

Animation::Animation(SpriteSheet & sprite_sheet, std::vector<AnimationFrame> animation_frames, int frame_width, int frame_height, int speed) 
    : sprite_sheet(sprite_sheet), animation_frames(animation_frames), frame_width(frame_width), frame_height(frame_height), speed(speed) {
    sprite.setTexture(sprite_sheet.texture);
    sprite.setScale(sprite_sheet.scale, sprite_sheet.scale);
}

void Animation::Update ()  {
    sf::IntRect current_frame_rect = sf::IntRect(
        animation_frames[current_frame_counter / speed].x * frame_width,
        animation_frames[current_frame_counter / speed].y * frame_height,
        frame_width, 
        frame_height
    );

    sprite.setTextureRect(current_frame_rect);
    if (current_frame_counter == (animation_frames.size() * speed) - speed) {
        current_frame_counter = 0;
    } else {
        current_frame_counter++;
    }
}

