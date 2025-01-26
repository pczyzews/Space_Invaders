#include "Gamemanager.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

GameManager::GameManager(Player* p) : player(p) {
    isRunning = true;
};

GameManager::~GameManager() {
    isRunning = false;
}

void GameManager::handleInput() {
    if(isRunning){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player->MoveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player->MoveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player->Shot();
        }
    }
}
