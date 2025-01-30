#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H
#include "Projectile.h"

class PlayerProjectile : public Projectile {
public:
    PlayerProjectile(float positionX, float positionY);
    void updatePosition() override;
};

#endif //PLAYERPROJECTILE_H
