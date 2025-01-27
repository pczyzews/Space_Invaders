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
    Player test(64, 64, 368, 600);
    AnimManager animationManager;
    GameManager manager(&test, &game);


    animationManager.loadAnimations(test, game);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("../textures/2player.png");

    animationManager.addAnimation(
    std::make_shared<Animation>(playerTexture, 16, 16, 2, 0.5f, true),
    test.getPositionXPtr(),
    test.getPositionYPtr(),
    test.getSizeX() / 16.0f,
    test.getSizeY() / 16.0f
);
    sf::Texture alienTexture1;
    alienTexture1.loadFromFile("../textures/2alien1.png");
    sf::Texture alienTexture2;
    alienTexture2.loadFromFile("../textures/2alien2.png");
    sf::Texture alienTexture3;
    alienTexture3.loadFromFile("../textures/2alien3.png");

    int alienCount = game.getAlienArmy().size();
    int quarter = alienCount / 4;
    int index = 0;

    for (const auto& alien : game.getAlienArmy()) {
        const sf::Texture* currentTexture = nullptr;

        if (index < quarter) {
            currentTexture = &alienTexture1;
        } else if (index < 2 * quarter) {
            currentTexture = &alienTexture2;
        } else {
            currentTexture = &alienTexture3;
        }

        animationManager.addAnimation(
            std::make_shared<Animation>(
                *currentTexture, 11, 11, 2, 0.3f, true
            ),
            alien->getPositionXPtr(),
            alien->getPositionYPtr(),
            alien->getSizeX() / 11.0f,
            alien->getSizeY() / 11.0f
        );

        ++index;
    }




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


            manager.handleInput();
            manager.movingAlienArmy(game);
            window.clear();

            // window.draw(test.getRect());
            // for (const auto& alien : game.getAlienArmy())
            // {
            //     window.draw(alien->getRect());
            // }

            test.update(deltaTime);
            test.draw(window);
            animationManager.updateAll(deltaTime);
            animationManager.drawAll(window);

            window.display();
        }

    }
