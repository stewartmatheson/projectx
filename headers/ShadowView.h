#pragma once

#include "HouseScene.h"
#include "View.h"
#include <SFML/Graphics.hpp>

class ShadowView : public View<HouseSceneState> {
    sf::Shader frag_shader;
    sf::RenderTexture render_texture;

  public:
    ShadowView(sf::IntRect);
    void Update();
    void Draw(sf::RenderTarget &render_target,
              const HouseSceneState &state) const;
};
