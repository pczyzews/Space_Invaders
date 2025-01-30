#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

class Game;
class AnimManager;

class CollisionDetector {
public:
    explicit CollisionDetector(AnimManager* animationManager);
    void checkForCollision(Game& game) const;

private:
    AnimManager* animationManager;
};

#endif // COLLISIONDETECTOR_H
