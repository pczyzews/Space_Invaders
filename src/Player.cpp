#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>


Player::Player(float sizeX, float sizeY, float positionX, float positionY)
    : Entity(sizeX, sizeY, positionX, positionY) {
}

Player::~Player() = default;

void Player::MoveLeft() {
    getRect().move(-1.0, 0.0);
    updatePosition(-1.0, 0);
}
void Player::MoveRight() {
    getRect().move(1.0, 0.0);
    updatePosition(1.0, 0);
}

void Player::Shot() {
    if (clock.getElapsedTime().asSeconds() >= 0.1f) {
        projectiles.push_back(std::make_shared<Projectile>(10.0, 20.0, getPositionX() + getSizeX() / 2 - 5, getPositionY(), true));
        clock.restart();
        std::cout << "Current number of projectiles: " << projectiles.size() << std::endl;
    }
}

void Player::updateProjectiles() {
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        (*it)->getRect().move(0, -5);
        (*it)->updatePosition(0, -5);

        if ((*it)->getPositionY() < 0) {
            it = projectiles.erase(it);
            std::cout << "Projectile removed" << std::endl;
        } else {
            ++it;
        }
    }
}

void Player::update(float deltaTime) {
    updateProjectiles();
}

void Player::draw(sf::RenderWindow& window) {
    for (auto& projectile : projectiles) {
        projectile->draw(window);
    }
}

std::vector<std::shared_ptr<Projectile>>& Player::getProjectiles()
{
    return projectiles;
}

void Player::die()
{
    alive = false;
}

bool Player::isAlive()
{
    return alive;
}
