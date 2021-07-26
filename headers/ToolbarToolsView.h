
#pragma once

#include "HouseSceneState.h"
#include "View.h"

class ToolbarToolsView : public View<HouseSceneState> {
    int window_width;
    const SpriteSheet &tool_map;

  public:
    ToolbarToolsView(SpriteSheet &);
    void Draw(sf::RenderTarget &, const HouseSceneState &) const;
    void Update();
};
