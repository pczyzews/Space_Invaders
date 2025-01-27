#include "Gamemanager.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

GameManager::GameManager(Player* p, Game* g) : player(p), game(g) {
    isRunning = true;
    lastMoveTime = std::chrono::steady_clock::now();
}

GameManager::~GameManager() {
    isRunning = false;
}

void GameManager::handleInput() {
    if(isRunning){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player->MoveRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player->MoveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) player->Shot();

    }
}

void GameManager::CalculateMaxPositions(float& min, float& max, Game& game) {
    min = 9999;
    max = -1;
    for (const auto& alien : game.getAlienArmy()) {
        if (alien->getPositionX() < min) {
            min = alien->getPositionX();
        }
        if (alien->getPositionX() + 30 > max) {
            max = alien->getPositionX() + 30;
        }
    }
}

void GameManager::movingAlienArmy(Game& game) {
    auto currentTime = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count() >= army_move_per_second) {
        if ((min_alien_position <= 10 || max_alien_position >= 790) && check_army_movement_down == false) {
            for (const auto& alien : game.getAlienArmy()) {
                alien->getRect().move(0, 10);
                alien->updatePosition(0, 10);
            }
            alien_step = -alien_step;
            check_army_movement_down = true;
            if (army_move_per_second >= 300) {
                army_move_per_second -= 100;
            }
        } else {
            for (const auto& alien : game.getAlienArmy()) {
                alien->getRect().move(alien_step, 0);
                alien->updatePosition(alien_step, 0);
            }
            check_army_movement_down = false;
        }

        CalculateMaxPositions(min_alien_position, max_alien_position, game);
        lastMoveTime = currentTime;
    }
}


