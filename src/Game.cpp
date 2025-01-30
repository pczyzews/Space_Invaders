#include "Game.h"

#include <iostream>
#include <ostream>

Game::Game()
{
    brickTexture = std::make_shared<sf::Texture>();
    brickTexture->loadFromFile("../textures/brick5.png");

    createArmy();
    createWall();
}

Game::~Game()=default;

void Game::createArmy() {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 15; i++) {
            alien_army.push_back(std::make_shared<Alien>(30, 30, 100 + 40 * i, 100 + 40 * j));
        }
    }
}

std::vector<std::shared_ptr<Alien>>& Game::getAlienArmy()
{
    return alien_army;
}

void Game::createWall() {
    for (int k = 0; k < 4; k++) {
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 5; i++) {
                if (j == 0 && (i == 1 || i == 2 || i == 3)) {
                    wall.push_back(std::make_shared<Brick>(20, 20, 40 + 207 * k + 20 * i, 480 + 20 * j, brickTexture));
                } else if (j == 1) {
                    wall.push_back(std::make_shared<Brick>(20, 20, 40 + 207 * k + 20 * i, 480 + 20 * j, brickTexture));
                } else if (j == 2 && (i == 0 || i == 4)) {
                    wall.push_back(std::make_shared<Brick>(20, 20, 40 + 207 * k + 20 * i, 480 + 20 * j, brickTexture));
                }
            }
        }
    }
}

std::vector<std::shared_ptr<Brick>>& Game::getWall()
{
    return wall;
}

void Game::clearWall() {
    wall.clear();
}


