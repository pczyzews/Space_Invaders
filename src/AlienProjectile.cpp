#include "AlienProjectile.h"


AlienProjectile::AlienProjectile(float positionX, float positionY) : Projectile(positionX, positionY)
{
    setTexture("../textures/fire0.png");
}


void AlienProjectile::updatePosition()
{
    setPositionY(2);
    getRect().move(0, 2);

}
