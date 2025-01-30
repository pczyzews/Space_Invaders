#include <Alien.h>
#include <random>
#include <Projectile.h>
#include <iostream>

#include "AlienFactory.h"
#include "AlienProjectile.h"
#include "AlienProjectileFactory.h"

Alien::Alien(float sizeX, float sizeY, float positionX, float positionY)
    : Entity(sizeX, sizeY, positionX, positionY) {
}

std::shared_ptr<Projectile> Alien::shoot()
{
    AlienProjectileFactory factory;
    return factory.createProjectile(getPositionX() + getSizeX() / 2 - 5, getPositionY());
}






