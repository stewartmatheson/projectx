#pragma once

#include "Controller.h"
#include "EventWithMouse.h"
#include "HouseScene.h"
#include "HouseSceneReducer.h"


class EditorController : Controller<HouseSceneReducer> {
    int tile_map_sprite_size;
    sf::RenderTexture& tile_palette_render_texture;
    sf::RenderTexture& house_render_texture;
    sf::Vector2i last_mouse_position;
    sf::Vector2i current_mouse_position;
public:
    EditorController(int, sf::RenderTexture&, sf::RenderTexture&);
    void Update(HouseSceneReducer&);
    void HandleInput(EventWithMouse, HouseSceneReducer&);
};


