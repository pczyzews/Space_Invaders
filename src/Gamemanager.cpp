#include "Gamemanager.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <chrono>
#include <iostream>

GameManager::GameManager(sf::RenderWindow& window ,Player* p, Game* g, AnimManager* animManager)
: window(window), player(p), game(g), animationManager(animManager) {
    isRunning = true;
    lastMoveTime = std::chrono::steady_clock::now();

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
                alien->alienShot(window);
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
                alien->alienShot(window);
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
                animationManager->collisionAnimation((*alienIt)->getPositionX(), (*alienIt)->getPositionY(), (*alienIt)->getSizeX(),(*alienIt)->getSizeY());
                animationManager->checkRemove(alienIt->get());
                projectileIt = player.getProjectiles().erase(projectileIt);
                alienIt = game.getAlienArmy().erase(alienIt);
                alienRemoved = true;
                game.getScore() += 10;
                std::cout << "SCORE: " << game.getScore() << std::endl;
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
    for (auto alienIt = game.getAlienArmy().begin(); alienIt != game.getAlienArmy().end();)
    {
        if ((*alienIt)->getHasShot())
        {
            if ((*alienIt)->getProjectile()->getPositionX() + (*alienIt)->getProjectile()->getSizeX() >= player.getPositionX() &&
                (*alienIt)->getProjectile()->getPositionX() <= player.getPositionX() + player.getSizeX() &&
                (*alienIt)->getProjectile()->getPositionY() + (*alienIt)->getProjectile()->getSizeY() >= player.getPositionY() &&
                (*alienIt)->getProjectile()->getPositionY() <= player.getPositionY() + player.getSizeY())
            {
                animationManager->collisionAnimation(player.getPositionX(), player.getPositionY(), player.getSizeX(),player.getSizeY());
                (*alienIt)->projectileReset();
                player.hit();
            }
        }
        ++alienIt;
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
         animationManager->getBoomTexture());

    animationManager->addAlienAnimations(game);
    animationManager->addPlayerAnimation(player);

    player->reset(400.f - player->getSizeX() / 2, 580.f);

}

void GameManager::drawLvlScore() {
    scoreText.setString("Score: " + std::to_string(game->getScore()));
    levelText.setString("Level: " + std::to_string(game->getLevel()));

    window.draw(scoreText);
    window.draw(levelText);
}

void GameManager::drawLives() {
    for (int i = 0; i < player->getLives(); ++i) {
        heartSprite.setPosition(20.f + i * 50, 660);
        window.draw(heartSprite);
    }
}

void GameManager::render() {
    drawLvlScore();
    drawLives();
}


void GameManager::displayStartScreen(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../textures/slkscr.ttf")) {
        std::cerr << "Nie można załadować czcionki!" << std::endl;
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
