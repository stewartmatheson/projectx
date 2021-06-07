#pragma once

#include "Controller.h"
#include "Map.h"
#include "EventWithMouse.h"
#include "HouseSceneState.h"
#include "HouseSceneReducer.h"

class EditorController : public Controller<HouseSceneReducer> {
    int tile_map_sprite_size;
    sf::RenderTexture& tile_palette_render_texture;
    sf::RenderTexture& house_render_texture;
    sf::Vector2i last_mouse_position;
    sf::Vector2i current_mouse_position;
    Map& map;
public:
    EditorController(int, sf::RenderTexture&, sf::RenderTexture&, Map&);
    void Update(HouseSceneReducer&);
    void HandleInput(EventWithMouse, HouseSceneReducer&);
};

