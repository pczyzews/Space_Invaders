#include "Projectile.h"
#include <iostream>

Projectile::Projectile(float positionX, float positionY) : positionX(std::make_shared<float>(positionX)), positionY(std::make_shared<float>(positionY)) {
    rect.setSize(sf::Vector2f(sizeX, sizeY));
    rect.setPosition(positionX, positionY);
}

Projectile::~Projectile() = default;

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(getRect());
}

float Projectile::getPositionX() const {
    return *positionX;
}

float Projectile::getPositionY() const {
    return *positionY;
}

void Projectile::setPositionX(const float x) const {
    (*positionX) = (*positionX) + x;
}

void Projectile::setPositionY(float y) const {
    (*positionY) = (*positionY) + y;
}

float Projectile::getSizeX() const {
    return sizeX;
}
float Projectile::getSizeY() const {
    return sizeY;
}

void Projectile::setTexture(const std::string& texturePath) {
    texture.loadFromFile(texturePath);
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture from: " << texturePath << std::endl;
    }
    rect.setTexture(&texture);
}

sf::RectangleShape& Projectile::getRect() {
    return rect;
}