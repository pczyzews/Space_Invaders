#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PlayerProjectileFactory.h"


Player::Player(float sizeX, float sizeY, float positionX, float positionY)
    : Entity(sizeX, sizeY, positionX, positionY) {
}


void Player::MoveLeft() {
    if (getPositionX() > 0) {
        updatePosition(-2.0, 0);
    }
}
void Player::MoveRight() {
    if (getPositionX() < 801 - 2 - getSizeX()) {
        updatePosition(2.0, 0);
    }
}


void Player::hit() {
    if (deathCooldown.getElapsedTime().asSeconds() >= deathCooldownTime) {
        lives --;
        reset(376,580);
        deathCooldown.restart();
        if (lives == 0) {
            die();
        }
    }
}

void Player::die()
{
    alive = false;
}

bool Player::isAlive() const
{
    return alive;
}

void Player::reset(float x, float y) {
    *getPositionXPtr() = x;
    *getPositionYPtr() = y;
    getRect().setPosition(x, y);

}

int Player::getLives() const {
    return lives;
}


std::shared_ptr<Projectile> Player::shoot()
{
    if (shootClock.getElapsedTime().asSeconds() < shootCooldown) {
        return nullptr;
    }
    try {
        PlayerProjectileFactory factory;
        std::shared_ptr<Projectile> newProjectile = factory.createProjectile(
            getPositionX() + getSizeX() / 2 - 5, getPositionY()
        );
        shootClock.restart();
        return newProjectile;
    } catch (const std::exception& e) {
        std::cerr << "Exception in Player::shoot: " << e.what() << std::endl;
        return nullptr;
    }
}

