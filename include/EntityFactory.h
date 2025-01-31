#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include <memory>

class Entity;

class EntityFactory {
public:
    virtual std::shared_ptr<Entity> createEntity(float positionX, float positionY)=0;
    virtual ~EntityFactory() = default;
};

#endif // ENTITYFACTORY_H