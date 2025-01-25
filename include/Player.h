#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
private:
public:
    Player(float sizeX, float sizeY, float positionX, float positionY);
    ~Player();

};

#endif //PLAYER_H
