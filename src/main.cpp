#include <SFML/Graphics.hpp>
#include "HouseScene.h"

int main(int argc, char** argv) {
    int window_width = 1920;
    int window_height = 1080;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
    window.setFramerateLimit(60);

    std::unique_ptr<HouseScene> current_scene = argc == 2 
        ? std::make_unique<HouseScene>(window_width, window_height, 20, 60, argv[1])
        : std::make_unique<HouseScene>(window_width, window_height, 20, 60, sf::IntRect(0, 0, 20, 20));
    
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if(event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

            current_scene->HandleInput(EventWithMouse{ event, sf::Mouse::getPosition(window) });
        }
        current_scene->Update();
        window.clear();
        current_scene->Draw(window);
        window.display();
    }

    return 0;
}

