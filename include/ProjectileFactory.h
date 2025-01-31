#ifndef PROJECTILEFACTORY_H
#define PROJECTILEFACTORY_H
#include <memory>

class Projectile;

class ProjectileFactory {
public:
    virtual std::shared_ptr<Projectile> createProjectile(float positionX, float positionY) = 0;
    virtual ~ProjectileFactory() = default;
};

#endif // PROJECTILEFACTORY_H