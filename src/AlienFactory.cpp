#include "AlienFactory.h"
#include "Alien.h"

std::shared_ptr<Entity> AlienFactory::createEntity(float positionX, float positionY)
{
    return std::make_shared<Alien>(30,30,positionX, positionY);
}