#include "Entity.h"
#include <iostream>

Entity::Entity(float sizeX, float sizeY, float positionX, float positionY)
    : sizeX(sizeX), sizeY(sizeY), positionX(positionX), positionY(positionY)
{
    rect.setSize(sf::Vector2f(sizeX, sizeY));
    rect.setPosition(positionX, positionY);
}

float Entity::getPositionX() const { return positionX; }
float Entity::getPositionY() const { return positionY; }

float Entity::getSizeX() const { return sizeX; }
float Entity::getSizeY() const { return sizeY; }

void Entity::setTexture(const std::string& texturePath)
{
    texture.loadFromFile(texturePath);
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture from: " << texturePath << std::endl;
    }
    rect.setTexture(&texture);
}
void Entity::updatePosition(float offsetX, float offsetY)
{
    positionX += offsetX;
    positionY += offsetY;
}

sf::RectangleShape& Entity::getRect(){ return rect; }

Entity::~Entity() = default;
