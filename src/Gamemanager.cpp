#include "Gamemanager.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

GameManager::GameManager(Player* p, Game* g, AnimManager* animManager) : player(p), game(g), animationManager(animManager) {
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
                army_move_per_second -= 200;
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

void GameManager::checkForCollision(Game& game,Player& player)
{
    for (auto alienIt = game.getAlienArmy().begin(); alienIt != game.getAlienArmy().end(); ) {
        bool alienRemoved = false;
        for (auto projectileIt = player.getProjectiles().begin(); projectileIt != player.getProjectiles().end(); ) {
            if ((*alienIt)->getPositionX() + (*alienIt)->getSizeX() >= (*projectileIt)->getPositionX() &&
                (*alienIt)->getPositionX() <= (*projectileIt)->getPositionX() + (*projectileIt)->getSizeX() &&
                (*alienIt)->getPositionY() + (*alienIt)->getSizeY() >= (*projectileIt)->getPositionY() &&
                (*alienIt)->getPositionY() <= (*projectileIt)->getPositionY() + (*projectileIt)->getSizeY())
            {
                animationManager->checkRemove(alienIt->get());
                projectileIt = player.getProjectiles().erase(projectileIt);
                alienIt = game.getAlienArmy().erase(alienIt);
                alienRemoved = true;
                game.score += 10;
                std::cout << "SCORE: " << game.score << std::endl;
                std::cout << "Liczba alienów: " << game.getAlienArmy().size() << std::endl;
                if (game.getAlienArmy().empty()) startNewLevel();
                break;
            }
            ++projectileIt;
        }
        if (!alienRemoved) {
            ++alienIt;
        }
    }
}

void GameManager::startNewLevel() {
    game->level += 1;
    game->createArmy();
    army_move_per_second = 1000;

    animationManager->clearAnimations();

    animationManager->loadTextures(
        animationManager->getPlayerTexture(),
        animationManager->getAlienTexture1(),
        animationManager->getAlienTexture2(),
        animationManager->getAlienTexture3());

    animationManager->addAlienAnimations(game);
    animationManager->addPlayerAnimation(player);
}


