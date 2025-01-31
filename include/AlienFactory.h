#ifndef ALIENFACTORY_H
#define ALIENFACTORY_H
#include "EntityFactory.h"

class Alien;

class AlienFactory : public EntityFactory {
public:
    std::shared_ptr<Entity> createEntity(float positionX, float positionY) override;
};

#endif // ALIENFACTORY_H