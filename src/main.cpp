#include <SFML/Graphics.hpp>
#include "HouseScene.h"

int main(int argc, char** argv) {
    int window_width = 1000;
    int window_height = 1000;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
    window.setFramerateLimit(60);
    
    Map map = argc == 2 ? Map(argv[1]) : Map(20, 20);
    HouseScene* current_scene = new HouseScene(map);

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

            current_scene->HandleInput(event);
        }
        current_scene->Update();
        current_scene->Draw(window);
    }

    return 0;
}

