#pragma once

#include "Controller.h"
#include "EventWithMouse.h"
#include "HouseSceneReducer.h"
#include "HouseSceneState.h"
#include "Map.h"
#include "Screen.h"
#include "ViewLayer.h"

class EditorController : public Controller<HouseSceneReducer> {
    int tile_map_sprite_size;
    sf::RenderTexture &tile_palette_render_texture;
    sf::RenderTexture &house_render_texture;
    sf::Vector2i last_mouse_position;
    std::shared_ptr<Screen> screen;
    ViewLayer& house_view_layer;
    ViewLayer& tile_palette_view;
    void HandleInputBoxSelection(const EventWithMouse &, HouseSceneReducer &);

  public:
    EditorController(int, sf::RenderTexture &, sf::RenderTexture &,
                     ViewLayer &, ViewLayer &);
    void Update(HouseSceneReducer &, sf::Time);
    void HandleInput(const EventWithMouse &, HouseSceneReducer &);
};
