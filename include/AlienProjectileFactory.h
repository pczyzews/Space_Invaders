#ifndef ALIENPROJECTILEFACTORY_H
#define ALIENPROJECTILEFACTORY_H
#include "ProjectileFactory.h"

class AlienProjectileFactory : public ProjectileFactory {
public:
    std::shared_ptr<Projectile> createProjectile(float positionX, float positionY) override;
};

#endif // ALIENPROJECTILEFACTORY_H