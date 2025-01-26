#ifndef ALIEN_H
#define ALIEN_H
#include "Entity.h"

class Alien : public Entity
{
    private:

    public:
        Alien(float sizeX, float sizeY, float positionX, float positionY);
        ~Alien();
};




#endif // ENTITY_H