#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Projectile.h"

class Player : public Entity
{
private:
    Projectile* player_bullet = nullptr;
public:
    Player(float sizeX, float sizeY, float positionX, float positionY);
    ~Player();
    void MoveLeft();
    void MoveRight();
    void Shot();

};

#endif //PLAYER_H
