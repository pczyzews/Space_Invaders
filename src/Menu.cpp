#include "Menu.h"
#include <iostream>
#include "Screen.h"
#include "Play.h"

Menu::Menu(Screen* screen) : screen(screen) {
    if (!font.loadFromFile("../textures/slkscr.ttf")) {
        std::cerr << "Error loading font.\n";
        exit(-1);
    }

    startText.setFont(font);
    startText.setString("START NEW GAME");
    startText.setCharacterSize(40);
    startText.setFillColor(sf::Color::White);
    startText.setPosition((800 - startText.getLocalBounds().width) / 2.0f, 200.0f);

    loadText.setFont(font);
    loadText.setString("LOAD GAME");
    loadText.setCharacterSize(40);
    loadText.setFillColor(sf::Color::White);
    loadText.setPosition((800 - loadText.getLocalBounds().width) / 2.0f, 300.0f);
}

std::shared_ptr<Gamestate> Menu::run(sf::Event& event, sf::RenderWindow* window) {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                  static_cast<float>(event.mouseButton.y));

            if (startText.getGlobalBounds().contains(mousePos)) {
                std::cout << "START NEW GAME has been clicked" << std::endl;
                return std::make_shared<Play>();
            }
        }
    }

    window->clear(sf::Color::Black);
    window->draw(startText);
    window->draw(loadText);
    window->display();

    return nullptr;
}
