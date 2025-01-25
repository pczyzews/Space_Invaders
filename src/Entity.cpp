#include "Entity.h"

Entity::Entity(float sizeX, float sizeY, float positionX, float positionY)
    : sizeX(sizeX), sizeY(sizeY), positionX(positionX), positionY(positionY)
{
    rect.setSize(sf::Vector2f(sizeX, sizeY));
    rect.setPosition(positionX, positionY);
}

float Entity::getPositionX() { return positionX; }
float Entity::getPositionY() { return positionY; }

void Entity::setTexture(const std::string& texturePath)
{
    texture.loadFromFile(texturePath);
    rect.setTexture(&texture);
}
void Entity::updatePosition(float offsetX, float offsetY)
{
    positionX += offsetX;
    positionY += offsetY;
}

sf::RectangleShape& Entity::getRect(){ return rect; }

Entity::~Entity() = default;
