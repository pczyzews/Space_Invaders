#include <Alien.h>
#include <Projectile.h>
#include <iostream>
#include "AlienProjectileFactory.h"

Alien::Alien(float sizeX, float sizeY, float positionX, float positionY)
    : Entity(sizeX, sizeY, positionX, positionY) {
}

std::shared_ptr<Projectile> Alien::shoot()
{
    try {
        AlienProjectileFactory factory;
        return factory.createProjectile(getPositionX() + getSizeX() / 2 - 5, getPositionY());
    } catch (const std::exception& e) {
        std::cerr << "Exception in Alien::shoot: " << e.what() << std::endl;
        return nullptr;
    }
}






