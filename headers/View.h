#pragma once

#include <SFML/Graphics.hpp>

template <typename T>
class View {
public: 
    virtual void Draw(sf::RenderTarget& render_target, const T& state) = 0;
};

