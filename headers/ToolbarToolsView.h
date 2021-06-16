
#pragma once

#include "View.h"
#include "HouseSceneState.h"

class ToolbarToolsView : public View<HouseSceneState> {
    int tile_palette_offset;
    int window_width;
    int toolbar_offset;
public:
    ToolbarToolsView(int, int, int);
    void Draw(sf::RenderTarget&, const HouseSceneState&) const;
};
