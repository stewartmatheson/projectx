
#pragma once

#include "View.h"
#include "HouseSceneState.h"

class ToolbarToolsView : public View<HouseSceneState> {
    int window_width;
    const SpriteSheet& tool_map;
public:
    ToolbarToolsView(SpriteSheet&);
    void Draw(sf::RenderTarget&, const HouseSceneState&) const;
};
