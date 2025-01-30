#include "GameOver.h"
#include "Menu.h"
#include "Play.h"
#include <iostream>

GameOver::GameOver() {
    if (!font.loadFromFile("../textures/slkscr.ttf")) {
        std::cerr << "Error loading font.\n";
        exit(-1);
    }

    overText.setFont(font);
    overText.setString("GAME OVER");
    overText.setCharacterSize(60);
    overText.setFillColor(sf::Color::White);
    overText.setPosition((800 - overText.getLocalBounds().width) / 2.0f, 200.0f);

    againText.setFont(font);
    againText.setString("CLICK TO PLAY AGAIN");
    againText.setCharacterSize(40);
    againText.setFillColor(sf::Color::White);
    againText.setPosition((800 - againText.getLocalBounds().width) / 2.0f, 450.0f);
}

std::shared_ptr<Gamestate> GameOver::run(sf::Event& event, sf::RenderWindow* window) {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                  static_cast<float>(event.mouseButton.y));

            if (againText.getGlobalBounds().contains(mousePos)) {
                againText.setFillColor(sf::Color::Red);
                std::cout << "CLICK TO PLAY AGAIN has been clicked" << std::endl;

                return std::make_shared<Play>();
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            againText.setFillColor(sf::Color::White);
        }

        window->clear(sf::Color::Black);
        window->draw(overText);
        window->draw(againText);
        window->display();
    }

    return nullptr;  // No state change
}
