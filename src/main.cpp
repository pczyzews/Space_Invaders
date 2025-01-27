#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Gamemanager.h"
#include "AnimManager.h"
#include "Alien.h"
#include <vector>
#include <thread>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);


    window.setFramerateLimit(144);

    Game game;
    Player test(64, 64, 368, 580);
    AnimManager animationManager;
    GameManager manager(window, &test, &game, &animationManager);


    sf::Texture playerTexture, alienTexture1, alienTexture2, alienTexture3;
    playerTexture.loadFromFile("../textures/2player.png");
    alienTexture1.loadFromFile("../textures/2alien1.png");
    alienTexture2.loadFromFile("../textures/2alien2.png");
    alienTexture3.loadFromFile("../textures/2alien3.png");

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
            manager.drawUI();

            //window.draw(test.getRect());
            test.update(deltaTime);
            test.draw(window);
            animationManager.updateAll(deltaTime);
            animationManager.drawAll(window);

            for (const auto& alien : game.getAlienArmy())
            {
                //window.draw(alien->getRect());
                alien->updateProjectile(window);
            }
            manager.checkForCollision(game, test);
        window.display();
        }

    }
