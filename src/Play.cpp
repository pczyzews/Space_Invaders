#include "Play.h"
#include <iostream>
#include "Game.h"
#include "AnimManager.h"
#include "Gamemanager.h"

Play::Play() {}

void Play::run(sf::Event& event,sf::RenderWindow* window)
{
    Game game;
    AnimManager animationManager;
    GameManager manager((*window), &game, &animationManager);


    sf::Texture playerTexture, alienTexture1, alienTexture2, alienTexture3, boomTexture;
    playerTexture.loadFromFile("../textures/2player.png");
    alienTexture1.loadFromFile("../textures/2alien1.png");
    alienTexture2.loadFromFile("../textures/2alien2.png");
    alienTexture3.loadFromFile("../textures/2alien3.png");
    boomTexture.loadFromFile("../textures/boom.png");

    animationManager.loadTextures(playerTexture, alienTexture1, alienTexture2, alienTexture3, boomTexture);
    animationManager.addPlayerAnimation(game.getPlayer());
    animationManager.addAlienAnimations(&game);

    manager.displayStartScreen((*window));

    sf::Clock clock;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        if (event.type == sf::Event::Resized)
        {
            window->setSize(sf::Vector2u(800, 700));
        }
        float deltaTime = clock.restart().asSeconds();

        window->clear();
        manager.handleInput();
        manager.movingAlienArmy(game);
        manager.render();
        animationManager.updateAll(deltaTime);
        animationManager.drawAll((*window));
        manager.drawProjectiles((*window));
        manager.updateProjectiles();
        manager.updateCollisions();
        manager.removeProjectiles();

        window->display();
    }
}
