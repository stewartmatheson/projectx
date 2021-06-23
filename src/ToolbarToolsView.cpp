#include <SFML/Graphics.hpp>
#include "ToolbarToolsView.h"

ToolbarToolsView::ToolbarToolsView(
    SpriteSheet& tool_map
) : tool_map(tool_map) {}

void ToolbarToolsView::Draw(sf::RenderTarget& render_target, const HouseSceneState& state) const {
    if(!state.editor_state.editor_enabled) {
        return;
    }

    sf::RectangleShape background;
    background.setPosition(0, 0);
    background.setSize(
        sf::Vector2f(
            state.window_width, 
            (state.editor_state.toolbar_icon_padding * 2) + tool_map.GetSpriteSize()
        )
    );
    background.setFillColor(sf::Color(60,60,60, 255));
    render_target.draw(background);

    int current_tool_count = 0;
    for(auto& tool : state.editor_state.tools) {
        sf::Sprite sprite_to_draw(tool_map.GetSprites()[tool.sprite_map_index]);
        sprite_to_draw.setPosition(
            state.editor_state.toolbar_icon_padding + (current_tool_count), 
            state.editor_state.toolbar_icon_padding
        );
        render_target.draw(sprite_to_draw);
        current_tool_count++;
    }
}
