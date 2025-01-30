#include <SFML/Graphics.hpp>
#include "Screen.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
    Screen screen(&window);
    while (window.isOpen())
    {
        sf::Event event;
        screen.run(event);
    }
}
