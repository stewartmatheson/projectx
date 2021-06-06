#pragma once

#include <SFML/Graphics.hpp>

template <typename T>
class View {
public: 
    virtual void Draw(sf::RenderTarget&, const T&) const = 0;
};

