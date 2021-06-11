#include "ViewLayer.h"

ViewLayer::ViewLayer(int view_height, int view_width) { 
    render_texture.create(view_width, view_height);
}

void ViewLayer::Draw(
    sf::RenderTarget& render_target, 
    const sf::View& view, 
    const HouseSceneState& house_scene_state)
{
    render_texture.setView(view);
    render_texture.clear();
    for(auto& view : views) {
        view->Draw(render_texture, house_scene_state);
    }
    
    render_texture.display();
    sf::Sprite texture_sprite(render_texture.getTexture());
    render_target.draw(texture_sprite);
}

sf::RenderTexture& ViewLayer::GetRenderTexture() {
    return render_texture;
}

void ViewLayer::AddView(std::shared_ptr<View<HouseSceneState>> view) {
    views.push_back(view);
}
