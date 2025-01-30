#include "PlayerProjectileFactory.h"

std::shared_ptr<Projectile> PlayerProjectileFactory::createProjectile(float positionX, float positionY) {
    return std::make_shared<PlayerProjectile>(positionX, positionY);
}