#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "Game.h"
#include "AnimManager.h"

class CollisionDetector {
public:
    explicit CollisionDetector(AnimManager* animationManager);
    void checkForCollision(Game& game);

private:
    AnimManager* animationManager;
};

#endif // COLLISIONDETECTOR_H
