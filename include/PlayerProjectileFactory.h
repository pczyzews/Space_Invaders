#ifndef PLAYERPROJECTILEFACTORY_H
#define PLAYERPROJECTILEFACTORY_H

#include "ProjectileFactory.h"
#include "PlayerProjectile.h"

class PlayerProjectileFactory : public ProjectileFactory {
public:
    std::shared_ptr<Projectile> createProjectile(float positionX, float positionY) override;
};

#endif // PLAYERPROJECTILEFACTORY_H