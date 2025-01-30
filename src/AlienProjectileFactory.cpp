#include "AlienProjectileFactory.h"
#include "AlienProjectile.h"

std::shared_ptr<Projectile> AlienProjectileFactory::createProjectile(float positionX, float positionY) {
    return std::make_shared<AlienProjectile>(positionX, positionY);
}