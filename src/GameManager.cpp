#include "GameManager.h"
#include <iostream>
#include "CollisionDetector.h"
#include "Game.h"
#include "Player.h"
#include "Alien.h"
#include <random>
#include "AnimManager.h"
#include "Projectile.h"
#include "Bunker.h"

GameManager::GameManager(sf::RenderWindow& window, Game* g, AnimManager* animManager)
    : window(window), game(g), animationManager(animManager) {
    isRunning = true;
    lastMoveTime = std::chrono::steady_clock::now();

    collisionDetector = new CollisionDetector(animationManager);

    if (!font.loadFromFile("../textures/slkscr.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);

    levelText.setFont(font);
    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(640.f, 10.f);

    if (!heartTexture.loadFromFile("../textures/heart2.png")) {
        std::cerr << "Failed to load heart texture!" << std::endl;
    }
    heartSprite.setTexture(heartTexture);
}

GameManager::~GameManager() {
    isRunning = false;
    delete collisionDetector;
    collisionDetector = nullptr;
}

void GameManager::handleInput() const
{
    if (isRunning) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            game->getPlayer()->MoveRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            game->getPlayer()->MoveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            std::shared_ptr<Projectile> newProjectile = game->getPlayer()->shoot();
            if (newProjectile) {
                game->getPlayerProjectiles().push_back(newProjectile);
            }
        }
    }
}

void GameManager::calculateMaxPositions(float& min, float& max, Game& game) {
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

void GameManager::movingAlienArmy(Game& game)
{
    const auto currentTime = std::chrono::steady_clock::now();
    const auto msSinceLastMove = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count();
    if (msSinceLastMove < army_move_per_second)
        return;

    float bottomMostY = 0.f;
    for (const auto& alien : game.getAlienArmy()) {
        const float alienBottom = alien->getPositionY() + 30;
        if (alienBottom > bottomMostY) {
            bottomMostY = alienBottom;
        }
    }

    calculateMaxPositions(min_alien_position, max_alien_position, game);

    const bool boundaryReached = (min_alien_position <= 10 || max_alien_position >= 790);

    if (boundaryReached) {
        if (bottomMostY < 400) {
            for (const auto& alien : game.getAlienArmy()) {
                alien->updatePosition(0, 10);
            }
            if (army_move_per_second >= 300) {
                army_move_per_second -= 100;
            }
        }
        alien_step = -alien_step;
    }

    for (const auto& alien : game.getAlienArmy()) {
        alien->updatePosition(alien_step, 0);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        const double randomValue = dis(gen);
        const double shooting_probability = static_cast<float>(game.getLevel()) / 100;
        if (randomValue < shooting_probability) {
            game.getAlienProjectiles().push_back(alien->shoot());
        }
    }

    lastMoveTime = currentTime;
}

void GameManager::startNewLevel() {
    game->increaseLevel(1);
    game->createArmy();
    game->clearWall();
    game->createWall();
    army_move_per_second = 1000;

    animationManager->clearAnimations();

    animationManager->loadTextures(
        animationManager->getPlayerTexture(),
        animationManager->getAlienTexture1(),
        animationManager->getAlienTexture2(),
        animationManager->getAlienTexture3(),
        animationManager->getBoomTexture()
    );

    animationManager->addAlienAnimations(game);
    animationManager->addPlayerAnimation(game->getPlayer());

    game->getPlayer()->reset(400.f - game->getPlayer()->getSizeX() / 2, 580.f);
}

void GameManager::removeProjectiles() const {
    auto& alienProjectiles = game->getAlienProjectiles();
    for (auto it = alienProjectiles.begin(); it != alienProjectiles.end(); ) {
        if ((*it)->getPositionY() > 700) {
            it = alienProjectiles.erase(it);
        } else {
            ++it;
        }
    }

    auto& playerProjectiles = game->getPlayerProjectiles();
    for (auto it = playerProjectiles.begin(); it != playerProjectiles.end(); ) {
        if ((*it)->getPositionY() < 0) {
            it = playerProjectiles.erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::drawLvlScore() {
    scoreText.setString("Score: " + std::to_string(game->getScore()));
    levelText.setString("Level: " + std::to_string(game->getLevel()));

    window.draw(scoreText);
    window.draw(levelText);
}

void GameManager::drawLives() {
    for (int i = 0; i < game->getPlayer()->getLives(); ++i) {
        heartSprite.setPosition(20.f + i * 50, 660);
        window.draw(heartSprite);
    }
}

void GameManager::drawProjectiles(sf::RenderWindow& window) const {
    for (auto& projectile : game->getPlayerProjectiles()) {
        projectile->draw(window);
    }
    for (auto& projectile : game->getAlienProjectiles()) {
        projectile->draw(window);
    }
}

void GameManager::updateProjectiles() const {
    for (auto& projectile : game->getPlayerProjectiles()) {
        projectile->updatePosition();
    }
    for (auto& projectile : game->getAlienProjectiles()) {
        projectile->updatePosition();
    }
}

void GameManager::drawBunkers() const {
    for (const auto& brick : game->getWall())
    {
        brick->draw(window);
    }
}

void GameManager::render() {
    drawLvlScore();
    drawBunkers();
    drawLives();
}

void GameManager::updateCollisions() {
    collisionDetector->checkForCollision(*game);
    if (game->getAlienArmy().empty())
    {
        startNewLevel();
    }
}

bool GameManager::playerStatus() const {
    return game->getPlayer()->isAlive();
}