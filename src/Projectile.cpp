#include "Projectile.h"
#include <iostream>

Projectile::Projectile(float sizeX, float sizeY, float positionX, float positionY, bool direction) : Entity(sizeX, sizeY, positionX, positionY), direction(direction)
{
    if (direction == true) {
        setTexture("../textures/fire1.png");
    }
}
Projectile::~Projectile(){}

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(getRect());
}
