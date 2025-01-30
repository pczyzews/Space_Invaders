#ifndef ALIENPROJECTILE_H
#define ALIENPROJECTILE_H
#include "Projectile.h"

class AlienProjectile : public Projectile {
public:
    AlienProjectile(float positionX, float positionY);
    void updatePosition() override;
};

#endif //ALIEN_PROJECTILE_H
