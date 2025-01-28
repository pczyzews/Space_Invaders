#ifndef ALIEN_H
#define ALIEN_H
#include <memory>
#include "Entity.h"

class Projectile;

class Alien : public Entity
{
    private:
        bool has_shot = false;
        std::shared_ptr<Projectile> projectile;
        double shooting_probability = 0.05;
    public:
        Alien(float sizeX, float sizeY, float positionX, float positionY);
        ~Alien();
        void alienShot(sf::RenderWindow& window);
        void updateProjectile(sf::RenderWindow& window);
        bool getHasShot();
        std::shared_ptr<Projectile> getProjectile();
        void projectileReset();

};

#endif // ALIEN_H