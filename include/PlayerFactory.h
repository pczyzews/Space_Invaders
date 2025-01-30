#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H
#include <memory>
#include "EntityFactory.h"

class PlayerFactory : public EntityFactory
{
public:
    std::shared_ptr<Entity> createEntity(float positionX, float positionY) override;
};

#endif // _H