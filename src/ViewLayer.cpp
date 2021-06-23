#include "ViewLayer.h"

ViewLayer::ViewLayer(sf::IntRect view_size) : view_size(view_size) { 
    render_texture.create(view_size.width, view_size.height);
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
    texture_sprite.setPosition(view_size.left, view_size.top);
    render_target.draw(texture_sprite);
}

sf::RenderTexture& ViewLayer::GetRenderTexture() {
    return render_texture;
}

void ViewLayer::AddView(std::unique_ptr<View<HouseSceneState>> &&view) {
    views.push_back(std::move(view));
}
