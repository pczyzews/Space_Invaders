#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player(float sizeX, float sizeY, float positionX, float positionY)
    : Entity(sizeX, sizeY, positionX, positionY)
{
    setTexture("../textures/player.png");
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
    if (player_bullet == nullptr) {
        player_bullet = new Projectile(10, 20, getPositionX() + 45, getPositionY(), true);
    }else
    {
        player_bullet->getRect().move(0, -5);
        player_bullet->updatePosition(0, -5);

        if (player_bullet->getPositionY() + player_bullet->getRect().getSize().y < 0)
        {
            delete player_bullet;
            player_bullet = nullptr;
        }
    }
}

