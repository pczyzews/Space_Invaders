#include "Menu.h"
#include <iostream>
#include "Screen.h"
#include "Play.h"

Menu::Menu(Screen* screen) : screen(screen)
{
    if (!font.loadFromFile("../textures/slkscr.ttf"))
    {
        std::cerr << "Error loading font.\n";
        exit(-1);
    }

    startText.setFont(font);
    startText.setString("START NEW GAME");
    startText.setCharacterSize(40);
    startText.setFillColor(sf::Color::White);
    float startX = (800 - startText.getLocalBounds().width) / 2.0f;
    float startY = 200.0f;
    startText.setPosition(startX, startY);

    loadText.setFont(font);
    loadText.setString("LOAD GAME");
    loadText.setCharacterSize(40);
    loadText.setFillColor(sf::Color::White);
    float loadX = (800 - loadText.getLocalBounds().width) / 2.0f;
    float loadY = 300.0f;
    loadText.setPosition(loadX, loadY);
}

void Menu::run(sf::Event& event, sf::RenderWindow* window)
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                  static_cast<float>(event.mouseButton.y));

            if (startText.getGlobalBounds().contains(mousePos))
            {
                startText.setFillColor(sf::Color::Red);
                std::cout << "START NEW GAME has been clicked" << std::endl;

                screen->changeState(new Play());
            }
            else if (loadText.getGlobalBounds().contains(mousePos))
            {
                loadText.setFillColor(sf::Color::Red);
                std::cout << "LOAD GAME has been clicked" << std::endl;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            startText.setFillColor(sf::Color::White);
            loadText.setFillColor(sf::Color::White);
        }

        window->clear(sf::Color::Black);
        window->draw(startText);
        window->draw(loadText);
        window->display();
    }
}
