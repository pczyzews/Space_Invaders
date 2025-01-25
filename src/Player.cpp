#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player(float sizeX, float sizeY, float positionX, float positionY)
    : Entity(sizeX, sizeY, positionX, positionY)
{
    setTexture("../include/player_texture.png");
}

Player::~Player() = default;
