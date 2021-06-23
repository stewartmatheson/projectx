#include "ToolbarController.h"

void ToolbarController::Update(HouseSceneReducer&) {}

void ToolbarController::HandleInput(const EventWithMouse& event_with_mouse, HouseSceneReducer& reducer) {
    if (event_with_mouse.event.type == sf::Event::MouseButtonReleased && 
        event_with_mouse.event.mouseButton.button == sf::Mouse::Left) {
        const auto state = reducer.GetState();
        auto first_button = sf::IntRect(
                state.editor_state.left_toolbar_width + state.editor_state.toolbar_icon_padding,
                state.editor_state.toolbar_icon_padding,
                state.editor_state.toolbar_icon_size * state.scale,
                state.editor_state.toolbar_icon_size * state.scale
        );

        if (first_button.contains(event_with_mouse.event.mouseButton.x, event_with_mouse.event.mouseButton.y)) {
            std::cout << "First toolbar button clicked" << std::endl;
        }
        
    }
}
