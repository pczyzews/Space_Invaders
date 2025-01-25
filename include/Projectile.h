#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Entity.h"

class Projectile : public Entity
{
private:
    bool direction;

public:
    Projectile(float sizeX, float sizeY, float positionX, float positionY, bool direction);
    ~Projectile();
};

#endif //PROJECTILE_H
