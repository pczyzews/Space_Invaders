#include <Alien.h>
#include <random>
#include <Projectile.h>
#include <iostream>

Alien::Alien(float sizeX, float sizeY, float positionX, float positionY)
    : Entity(sizeX, sizeY, positionX, positionY) {
}

Alien::~Alien()=default;


void Alien::updateProjectile(sf::RenderWindow& window)
{
    if (has_shot)
    {
        projectile->getRect().move(0, 5);
        projectile->updatePosition(0,5);
        projectile -> draw(window);
        if (projectile->getPositionY() > 700)
        {
            projectile.reset();
            has_shot = false;
        }
    }

}

void Alien::alienShot(sf::RenderWindow& window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double randomValue = dis(gen);
    if (randomValue < shooting_probability && has_shot == false)
    {
        projectile = std::make_shared<Projectile>(10.0, 20.0, getPositionX() + getSizeX()/2 - 5, getPositionY(), false);
        projectile -> draw(window);
        has_shot = true;
    }
}

bool Alien::getHasShot()
{
    return has_shot;
}

std::shared_ptr<Projectile> Alien::getProjectile()
{
    return projectile;
}


void Alien::updateShootingProbability(float level)
{
    shooting_probability += level;
}

