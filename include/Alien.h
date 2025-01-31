#ifndef ALIEN_H
#define ALIEN_H
#include "Entity.h"

class Alien : public Entity {
    public:
        Alien(float sizeX, float sizeY, float positionX, float positionY);
        std::shared_ptr<Projectile> shoot() override;
};

#endif // ALIEN_H