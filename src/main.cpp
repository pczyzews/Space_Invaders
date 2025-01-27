#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Gamemanager.h"
#include "AnimManager.h"
#include "Alien.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);

    Game game;
    Player test(64, 64, 368, 600);
    AnimManager animationManager;
    GameManager manager(&test, &game, &animationManager);


    //animationManager.loadAnimations(&test, &game);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../textures/2player.png")) {
        std::cerr << "Błąd podczas ładowania tekstury gracza!" << std::endl;
    }

    sf::Texture alienTexture1;
    if (!alienTexture1.loadFromFile("../textures/2alien1.png")) {
        std::cerr << "Błąd podczas ładowania tekstury 2alien1!" << std::endl;
    }

    sf::Texture alienTexture2;
    if (!alienTexture2.loadFromFile("../textures/2alien2.png")) {
        std::cerr << "Błąd podczas ładowania tekstury 2alien2!" << std::endl;
    }

    sf::Texture alienTexture3;
    if (!alienTexture3.loadFromFile("../textures/2alien3.png")) {
        std::cerr << "Błąd podczas ładowania tekstury 2alien3!" << std::endl;
    }

    animationManager.loadTextures(playerTexture, alienTexture1, alienTexture2, alienTexture3);
    animationManager.addPlayerAnimation(&test);
    animationManager.addAlienAnimations(&game);



    sf::Clock clock;

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
            float deltaTime = clock.restart().asSeconds();

            window.clear();
            manager.handleInput();
            manager.movingAlienArmy(game);

            // window.draw(test.getRect());
            // for (const auto& alien : game.getAlienArmy())
            // {
            //     window.draw(alien->getRect());
            // }

            test.update(deltaTime);
            test.draw(window);
            animationManager.updateAll(deltaTime);
            animationManager.drawAll(window);
            //animationManager.checkRemove();


            manager.checkForCollision(game, test);

            window.display();
        }

    }
