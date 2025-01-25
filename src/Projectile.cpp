#include "Projectile.h"

Projectile::Projectile(float sizeX, float sizeY, float positionX, float positionY, bool direction) : Entity(sizeX, sizeY, positionX, positionY), direction(direction)
{
    if (direction == true) {
        setTexture("../include/bullet_player.png");
    }
}
Projectile::~Projectile(){}
