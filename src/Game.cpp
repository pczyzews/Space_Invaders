#include "Game.h"

Game::Game()
{
    createArmy();
}

Game::~Game()=default;
std::vector<std::shared_ptr<Alien>>& Game::getAlienArmy()
{
    return alien_army;
}

void Game::createArmy() {
    sf::Texture alienTexture;
    alienTexture.loadFromFile("../textures/2alien1.png");

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 15; i++) {
            alien_army.push_back(std::make_shared<Alien>(30, 30, 100 + 40 * i, 100 + 40 * j));
        }
    }
}



