#pragma once 

#include <memory>
#include "View.h"
#include "HouseSceneState.h"

class ViewLayer {
    std::vector<std::unique_ptr<View<HouseSceneState>>> views;
    sf::RenderTexture render_texture;
    sf::IntRect view_size;
public: 
    ViewLayer(sf::IntRect);
    void Draw(sf::RenderTarget&, const sf::View&, const HouseSceneState&);
    void AddView(std::unique_ptr<View<HouseSceneState>> &&view);
    sf::RenderTexture& GetRenderTexture();
};


