#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Projectile.h"
#include "Animation.h"
#include <vector>
#include <memory>


class Player : public Entity {
private:
    Animation animation;
    double weaponCooldown = 0.0;
    std::vector<std::shared_ptr<Projectile>> projectiles;

public:
    Player(float sizeX, float sizeY, float positionX, float positionY, const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameDuration);
    ~Player();
    void MoveLeft();
    void MoveRight();
    void Shot();
    void update();
    void draw(sf::RenderWindow& window);
    void updateProjectiles();


};

#endif //PLAYER_H
