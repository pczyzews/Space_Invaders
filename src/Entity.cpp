#include "Entity.h"
#include <iostream>

Entity::Entity(float sizeX, float sizeY, float posX, float posY)
    : sizeX(sizeX), sizeY(sizeY),
      positionX(std::make_shared<float>(posX)),
      positionY(std::make_shared<float>(posY))
{
    rect.setSize(sf::Vector2f(sizeX, sizeY));
    rect.setPosition(posX, posY);
    lives = 0;
}

float Entity::getPositionX() const { return *positionX; }
float Entity::getPositionY() const { return *positionY; }

float Entity::getSizeX() const { return sizeX; }
float Entity::getSizeY() const { return sizeY; }

void Entity::setTexture(const std::string& texturePath)
{
    try {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
        rect.setTexture(&texture);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in setTexture: " << e.what() << std::endl;
    }
}
void Entity::updatePosition(float offsetX, float offsetY)
{
    *positionX += offsetX;
    *positionY += offsetY;

    rect.setPosition(*positionX, *positionY);
    rect.move(offsetX, offsetY);
}

sf::RectangleShape& Entity::getRect(){ return rect; }



Entity::~Entity() = default;


