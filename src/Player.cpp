#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>


Player::Player(float sizeX, float sizeY, float positionX, float positionY, const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameDuration)
    : Entity(sizeX, sizeY, positionX, positionY), animation(texture, frameWidth, frameHeight, frameCount, frameDuration) {
    animation.setPosition(positionX, positionY);
    animation.setScale(sizeX/frameWidth, sizeY/frameHeight);
    animation.play();
}

Player::~Player() = default;

void Player::MoveLeft() {
    getRect().move(-1.0, 0.0);
    updatePosition(-1.0, 0);
    animation.setPosition(getPositionX(), getPositionY());
}
void Player::MoveRight() {
    getRect().move(1.0, 0.0);
    updatePosition(1.0, 0);
    animation.setPosition(getPositionX(), getPositionY());
}

double GetTime() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(now.time_since_epoch());
    return duration.count();
}

void Player::Shot() {
    double currentTime = GetTime();

    if (currentTime - weaponCooldown >= 0.4) {
        projectiles.push_back(std::make_shared<Projectile>(10.0, 20.0, getPositionX() + getSizeX()/2 - 5, getPositionY(), true));
        weaponCooldown = currentTime;
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

void Player::update() {
    animation.update();
    updateProjectiles();
}
void Player::draw(sf::RenderWindow& window) {
    animation.draw(window);
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
