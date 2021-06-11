#pragma once 

#include <memory>
#include "View.h"
#include "HouseSceneState.h"

class ViewLayer {
    std::vector<std::shared_ptr<View<HouseSceneState>>> views;
    sf::RenderTexture render_texture;
public: 
    ViewLayer(int, int);
    void Draw(sf::RenderTarget&, const sf::View&, const HouseSceneState&);
    void AddView(std::shared_ptr<View<HouseSceneState>> view);
    sf::RenderTexture& GetRenderTexture();
};


