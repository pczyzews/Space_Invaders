#include <boost/test/unit_test.hpp>
#include "CollisionDetector.h"
#include "Game.h"
#include "Projectile.h"
#include "Player.h"
#include "Alien.h"
#include "Bunker.h"
#include "AnimManager.h"
#include <memory>
#include "AlienProjectile.h"
#include "PlayerProjectile.h"


BOOST_AUTO_TEST_SUITE(CollisionDetectorTests)

BOOST_AUTO_TEST_CASE(ProjectileHitsAlienTest)
{
    AnimManager animManager;
    CollisionDetector detector(&animManager);
    Game game;

    std::shared_ptr<Alien> alien = std::make_shared<Alien>(30, 30, 900, 900);
    game.getAlienArmy().push_back(alien);

    std::shared_ptr<Projectile> projectile = std::make_shared<PlayerProjectile>(900, 900);
    game.getPlayerProjectiles().push_back(projectile);

    detector.checkForCollision(game);

    BOOST_TEST(game.getAlienArmy().size() == 60);

    BOOST_TEST(game.getScore() == 10);
}

BOOST_AUTO_TEST_CASE(AlienProjectileHitsPlayerTest)
{
    AnimManager animManager;
    CollisionDetector detector(&animManager);
    Game game;

    game.getPlayer() = std::make_shared<Player>(50, 50, 200, 300);

    std::shared_ptr<Projectile> projectile = std::make_shared<AlienProjectile>(200, 300);
    game.getAlienProjectiles().push_back(projectile);

    detector.checkForCollision(game);

    BOOST_TEST(game.getAlienProjectiles().empty());
}

BOOST_AUTO_TEST_CASE(ProjectileMissesTargetTest)
{
    AnimManager animManager;
    CollisionDetector detector(&animManager);
    Game game;

    std::shared_ptr<Projectile> projectile = std::make_shared<PlayerProjectile>(700, 800);
    game.getPlayerProjectiles().push_back(projectile);

    detector.checkForCollision(game);

    BOOST_TEST(game.getPlayerProjectiles().size() == 1);
}

BOOST_AUTO_TEST_SUITE_END()