#include "CollisionDetector.h"
#include <iostream>

CollisionDetector::CollisionDetector(AnimManager* animationManager)
    : animationManager(animationManager) {
}

void CollisionDetector::checkForCollision(Game& game)
{
    for (auto alienIt = game.getAlienArmy().begin(); alienIt != game.getAlienArmy().end(); ) {
        bool alienRemoved = false;

        for (auto playerProjectileIt = game.getPlayerProjectiles().begin();
             playerProjectileIt != game.getPlayerProjectiles().end(); )
        {
            if ((*alienIt)->getPositionX() + (*alienIt)->getSizeX() >= (*playerProjectileIt)->getPositionX() &&
                (*alienIt)->getPositionX() <= (*playerProjectileIt)->getPositionX() + (*playerProjectileIt)->getSizeX() &&
                (*alienIt)->getPositionY() + (*alienIt)->getSizeY() >= (*playerProjectileIt)->getPositionY() &&
                (*alienIt)->getPositionY() <= (*playerProjectileIt)->getPositionY() + (*playerProjectileIt)->getSizeY())
            {
                animationManager->collisionAnimation((*alienIt)->getPositionX(),
                                                     (*alienIt)->getPositionY(),
                                                     (*alienIt)->getSizeX(),
                                                     (*alienIt)->getSizeY());
                std::shared_ptr<Entity> entity = std::static_pointer_cast<Entity>(*alienIt);
                animationManager->checkRemove(entity);

                playerProjectileIt = game.getPlayerProjectiles().erase(playerProjectileIt);

                alienIt = game.getAlienArmy().erase(alienIt);
                alienRemoved = true;

                game.getScore() += 10;
                std::cout << "SCORE: " << game.getScore() << std::endl;
                std::cout << "Aliens left: " << game.getAlienArmy().size() << std::endl;

                if (game.getAlienArmy().empty()) {
                }

                break;
            }
            ++playerProjectileIt;

        }

        if (!alienRemoved) {
            ++alienIt;
        }
    }

    for (auto alienProjectileIt = game.getAlienProjectiles().begin();
         alienProjectileIt != game.getAlienProjectiles().end(); )
    {
        if ((*alienProjectileIt)->getPositionX() + (*alienProjectileIt)->getSizeX() >= game.getPlayer()->getPositionX() &&
            (*alienProjectileIt)->getPositionX() <= game.getPlayer()->getPositionX() + game.getPlayer()->getSizeX() &&
            (*alienProjectileIt)->getPositionY() + (*alienProjectileIt)->getSizeY() >= game.getPlayer()->getPositionY() &&
            (*alienProjectileIt)->getPositionY() <= game.getPlayer()->getPositionY() + game.getPlayer()->getSizeY())
        {
            animationManager->collisionAnimation(game.getPlayer()->getPositionX(),
                                                 game.getPlayer()->getPositionY(),
                                                 game.getPlayer()->getSizeX(),
                                                 game.getPlayer()->getSizeY());

            alienProjectileIt = game.getAlienProjectiles().erase(alienProjectileIt);

            game.getPlayer()->hit();
        }
        else {
            ++alienProjectileIt;
        }
    }
}
