#pragma once

#include "HouseSceneState.h"
#include "View.h"
#include <memory>

class ViewLayer {
    std::vector<std::unique_ptr<View<HouseSceneState>>> views;
    sf::RenderTexture render_texture;
    sf::IntRect view_size;

  public:
    ViewLayer(sf::IntRect);
    void Draw(sf::RenderTarget &, const sf::View &, const HouseSceneState &);
    void AddView(std::unique_ptr<View<HouseSceneState>> &&view);
    sf::RenderTexture &GetRenderTexture();
};
