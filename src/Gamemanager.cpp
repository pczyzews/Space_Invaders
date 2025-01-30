#include "GameManager.h"
#include "Player.h"
#include "AlienProjectile.h"
#include "CollisionDetector.h"
#include <random>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

GameManager::GameManager(sf::RenderWindow& window, Game* g, AnimManager* animManager)
    : window(window), game(g), animationManager(animManager)
{
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
    levelText.setPosition(650.f, 10.f);

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

void GameManager::handleInput() {
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

void GameManager::movingAlienArmy(Game& game) {
    auto currentTime = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count() >= army_move_per_second) {
        if ((min_alien_position <= 10 || max_alien_position >= 790) && check_army_movement_down == false) {
            for (const auto& alien : game.getAlienArmy()) {
                alien->updatePosition(0, 10);
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, 1.0);

                double randomValue = dis(gen);
                double shooting_probability = game.getLevel() * 0.05;
                if (randomValue < shooting_probability) {
                    game.getAlienProjectiles().push_back(alien->shoot());
                }
            }
            alien_step = -alien_step;
            check_army_movement_down = true;
            if (army_move_per_second >= 300) {
                army_move_per_second -= 100;
            }
        } else {
            for (const auto& alien : game.getAlienArmy()) {
                alien->updatePosition(alien_step, 0);

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, 1.0);
                double randomValue = dis(gen);
                double shooting_probability = game.getLevel() * 0.05;
                if (randomValue < shooting_probability) {
                    game.getAlienProjectiles().push_back(alien->shoot());
                }
            }
            check_army_movement_down = false;
        }

        calculateMaxPositions(min_alien_position, max_alien_position, game);
        lastMoveTime = currentTime;
    }
}

void GameManager::startNewLevel() {
    game->getLevel() += 1;
    game->createArmy();
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

void GameManager::removeProjectiles() {
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

void GameManager::drawProjectiles(sf::RenderWindow& window) {
    for (auto& projectile : game->getPlayerProjectiles()) {
        projectile->draw(window);
    }
    for (auto& projectile : game->getAlienProjectiles()) {
        projectile->draw(window);
    }
}

void GameManager::updateProjectiles() {
    for (auto& projectile : game->getPlayerProjectiles()) {
        projectile->updatePosition();
    }
    for (auto& projectile : game->getAlienProjectiles()) {
        projectile->updatePosition();
    }
}

void GameManager::render() {
    drawLvlScore();
    drawLives();
}
void GameManager::updateCollisions() {
    collisionDetector->checkForCollision(*game);
    if (game->getAlienArmy().empty()) {
        startNewLevel();
    }
}

void GameManager::displayStartScreen(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../textures/slkscr.ttf")) {
        std::cerr << "Cannot load font!" << std::endl;
        return;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Space Invaders");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setPosition(120, 250);

    sf::Text startText;
    startText.setFont(font);
    startText.setString("Press ENTER to Start");
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(240, 500);

    sf::Clock blinkClock;
    bool showText = true;
    bool gameStarted = false;

    while (window.isOpen() && !gameStarted) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                gameStarted = true;
            }
        }

        if (blinkClock.getElapsedTime().asSeconds() > 0.5f) {
            showText = !showText;
            blinkClock.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        if (showText) {
            window.draw(startText);
        }
        window.display();
    }
}
