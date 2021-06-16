#include <SFML/Graphics.hpp>
#include "ToolbarToolsView.h"

ToolbarToolsView::ToolbarToolsView(int tile_palette_offset, int window_width, int toolbar_offset) : 
tile_palette_offset(tile_palette_offset), 
window_width(window_width), 
toolbar_offset(toolbar_offset) {}


void ToolbarToolsView::Draw(sf::RenderTarget& render_target, const HouseSceneState& state) const {
    if(!state.editor_state.editor_enabled) {
        return;
    }

    sf::RectangleShape background;
    background.setPosition(tile_palette_offset, 0);
    background.setSize(sf::Vector2f(window_width, toolbar_offset));
    background.setFillColor(sf::Color(60,60,60, 255));
    render_target.draw(background);
}
