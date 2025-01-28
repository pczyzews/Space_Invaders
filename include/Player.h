#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Projectile.h"
#include "Animation.h"
#include <vector>
#include <memory>

using ProjectileVector = std::vector<std::shared_ptr<Projectile>>;

class Player : public Entity {
private:
    bool alive = true;
    double weaponCooldown = 0.0;
    ProjectileVector projectiles;
    sf::Clock clock, deathCooldown;
    const float deathCooldownTime = 2.0f;
    int lives = 3;

public:
    Player(float sizeX, float sizeY, float positionX, float positionY);
    ~Player();
    void MoveLeft();
    void MoveRight();
    void Shot();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void updateProjectiles();
    std::vector<std::shared_ptr<Projectile>>& getProjectiles();
    void hit();
    void die();
    bool isAlive();
    void reset(float x, float y);
    int getLives() const;
};

#endif //PLAYER_H
