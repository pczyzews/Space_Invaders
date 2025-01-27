#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Gamemanager.h"
#include "Alien.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);


    window.setFramerateLimit(144);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("../textures/2player.png");

    if (playerTexture.loadFromFile("../textures/2player.png")) {
        std::cerr << "Udało się załadować teksturę!" << std::endl;
    }

    Player test(64, 64, 368, 600, playerTexture, 16, 16,2 ,0.5);
    Game game;
    GameManager manager(&test);


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::Resized)
            {
                window.setSize(sf::Vector2u(800, 700));
            }


        manager.handleInput();
        manager.movingAlienArmy(game);
        window.clear();
        //window.draw(test.getRect());
            test.update();
            test.draw(window);
            for (const auto& alien : game.getAlienArmy())
            {
                window.draw(alien->getRect());
            }
            manager.checkForCollision(game, test);
        window.display();
        }

    }
