#include "PlayerFactory.h"

#include "Player.h"

std::shared_ptr<Entity> PlayerFactory::createEntity(float positionX, float positionY) {
    return std::make_shared<Player>(48, 48, positionX, positionY);
}