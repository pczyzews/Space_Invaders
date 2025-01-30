#include <iostream>
#include <SFML/Graphics.hpp>
#include "Screen.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);
    Screen screen(&window);

    while (window.isOpen()) {
        sf::Event event;
        screen.run(event);
    }

    return 0;
}