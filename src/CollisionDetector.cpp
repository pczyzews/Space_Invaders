#include "CollisionDetector.h"
#include "Projectile.h"
#include "Game.h"
#include "AnimManager.h"
#include <iostream>
#include "Alien.h"
#include "Bunker.h"
#include "Player.h"

CollisionDetector::CollisionDetector(AnimManager* animationManager)
    : animationManager(animationManager) {
}

void CollisionDetector::checkForCollision(Game& game) const
{
    try
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

                    game.increaseScore(10);
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
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught in checkForCollision: " << e.what() << std::endl;
    }

    try
    {
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
    }catch (const std::exception& e) {
        std::cerr << "Exception caught in checkForCollision: " << e.what() << std::endl;
    }


    try
    {
        for (auto projectileIt = game.getPlayerProjectiles().begin(); projectileIt != game.getPlayerProjectiles().end(); ) {
            bool projectileRemoved = false;
            for (auto wallIt = game.getWall().begin(); wallIt != game.getWall().end(); ) {
                if ((*wallIt)->getPositionX() + (*wallIt)->getSizeX() >= (*projectileIt)->getPositionX() &&
                    (*wallIt)->getPositionX() <= (*projectileIt)->getPositionX() + (*projectileIt)->getSizeX() &&
                    (*wallIt)->getPositionY() + (*wallIt)->getSizeY() >= (*projectileIt)->getPositionY() &&
                    (*wallIt)->getPositionY() <= (*projectileIt)->getPositionY() + (*projectileIt)->getSizeY())
                {
                    (*wallIt)->hit();
                    if ((*wallIt)->isDestroyed()) {
                        wallIt = game.getWall().erase(wallIt);
                    } else {
                        ++wallIt;
                    }
                    projectileIt = game.getPlayerProjectiles().erase(projectileIt);
                    projectileRemoved = true;
                    break;
                }
                ++wallIt;
            }
            if (!projectileRemoved) {
                ++projectileIt;
            }
        }
    }  catch (const std::exception& e) {
            std::cerr << "Exception caught in checkForCollision: " << e.what() << std::endl;
        }
       try
       {
           for (auto projectileIt = game.getAlienProjectiles().begin(); projectileIt != game.getAlienProjectiles().end(); ) {
               bool projectileRemoved = false;
               for (auto wallIt = game.getWall().begin(); wallIt != game.getWall().end(); ) {
                   if ((*wallIt)->getPositionX() + (*wallIt)->getSizeX() >= (*projectileIt)->getPositionX() &&
                       (*wallIt)->getPositionX() <= (*projectileIt)->getPositionX() + (*projectileIt)->getSizeX() &&
                       (*wallIt)->getPositionY() + (*wallIt)->getSizeY() >= (*projectileIt)->getPositionY() &&
                       (*wallIt)->getPositionY() <= (*projectileIt)->getPositionY() + (*projectileIt)->getSizeY())
                   {
                       (*wallIt)->hit();
                       if ((*wallIt)->isDestroyed()) {
                           wallIt = game.getWall().erase(wallIt);
                       } else {
                           ++wallIt;
                       }
                       projectileIt = game.getAlienProjectiles().erase(projectileIt);
                       projectileRemoved = true;
                       break;
                   }
                   ++wallIt;
               }
               if (!projectileRemoved) {
                   ++projectileIt;
               }
           }
       }catch (const std::exception& e) {
           std::cerr << "Exception caught in checkForCollision: " << e.what() << std::endl;
       }
}
