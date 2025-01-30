#include "Game.h"
#include "AlienFactory.h"
#include "PlayerFactory.h"
#include <iostream>

Game::Game()
{
    brickTexture = std::make_shared<sf::Texture>();
    brickTexture->loadFromFile("../textures/brick5.png");
    startGame();
    createWall();
}

Game::~Game()=default;


std::vector<std::shared_ptr<Alien>>& Game::getAlienArmy()
{
    return alien_army;
}

std::shared_ptr<Player>& Game::getPlayer()
{
    return player;
}

std::vector<std::shared_ptr<Projectile>>& Game::getAlienProjectiles()
{
    return alienProjectiles;
}

std::vector<std::shared_ptr<Projectile>>& Game::getPlayerProjectiles()
{
    return playerProjectiles;
}


void Game::createArmy() {
    AlienFactory factory;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 15; i++) {
            std::shared_ptr<Alien> alien = std::dynamic_pointer_cast<Alien>(factory.createEntity( 100 + 40 * i, 100 + 40 * j));
            if (alien) {
                alien_army.push_back(alien);
            } else {
                std::cerr << "Failed to cast Entity to Alien!" << std::endl;
            }
        }
    }
    std::cout << "Alien size:" << alien_army.size() << std::endl;
}

void Game::createWall() {
    for (int k = 0; k < 4; k++) {
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 5; i++) {
                if (j == 0 && (i == 1 || i == 2 || i == 3)) {
                    wall.push_back(std::make_shared<Bunker>(20, 20, 40 + 207 * k + 20 * i, 480 + 20 * j, brickTexture));
                } else if (j == 1) {
                    wall.push_back(std::make_shared<Bunker>(20, 20, 40 + 207 * k + 20 * i, 480 + 20 * j, brickTexture));
                } else if (j == 2 && (i == 0 || i == 4)) {
                    wall.push_back(std::make_shared<Bunker>(20, 20, 40 + 207 * k + 20 * i, 480 + 20 * j, brickTexture));
                }
            }
        }
    }
}


int& Game::getLevel()
{
    return level;
}
int& Game::getScore()
{
    return score;
}


void Game::startGame()
{
    PlayerFactory player_factory;
    player = std::dynamic_pointer_cast<Player>(player_factory.createEntity(376, 580));
    createArmy();
}

std::vector<std::shared_ptr<Bunker>>& Game::getWall()
{
    return wall;
}
void Game::clearWall() {
    wall.clear();
}


