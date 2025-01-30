#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include <SFML/System/Clock.hpp>


using ProjectileVector = std::vector<std::shared_ptr<Projectile>>;

class Player : public Entity {
private:
    bool alive = true;
    double weaponCooldown = 0.0;
    sf::Clock clock, deathCooldown, shootClock;
    const float shootCooldown = 0.1f;
    const float deathCooldownTime = 2.0f;
    int lives = 3;

public:
    Player(float sizeX, float sizeY, float positionX, float positionY);
    void MoveLeft();
    void MoveRight();
    void hit();
    void die();
    bool isAlive() const;
    void reset(float x, float y);
    int getLives() const;
    std::shared_ptr<Projectile> shoot() override;
};

#endif //PLAYER_H
