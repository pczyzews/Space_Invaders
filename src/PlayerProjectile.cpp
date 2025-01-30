#include "PlayerProjectile.h"

PlayerProjectile::PlayerProjectile(float positionX, float positionY) : Projectile(positionX, positionY)
{
    setTexture("../textures/fire1.png");
}


void PlayerProjectile::updatePosition()
{
    setPositionY(-2);
    getRect().move(0, -2);

}
