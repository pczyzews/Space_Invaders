#include <boost/test/unit_test.hpp>

#include "GameManager.h"
#include "Game.h"
#include "AlienFactory.h"
#include "AlienProjectileFactory.h"
#include "PlayerProjectileFactory.h"
#include "AnimManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Projectile.h"

BOOST_AUTO_TEST_SUITE(TestGameManager)

BOOST_AUTO_TEST_CASE(GameManager_InitializationTest)
{
    sf::RenderWindow window;
    Game game;
    AnimManager animManager;
    GameManager gm(window, &game, &animManager);

    BOOST_CHECK_EQUAL(gm.playerStatus(), true);
}

BOOST_AUTO_TEST_CASE(GameManager_CalculateMaxPositionsTest)
{
    sf::RenderWindow window;
    Game game;
    AnimManager animManager;
    GameManager gm(window, &game, &animManager);
    AlienFactory alienFactory;

    game.createArmy();

    float min = -1000, max = 1000;

    GameManager::calculateMaxPositions(min, max, game);
    BOOST_CHECK_EQUAL(min, 100);
    BOOST_CHECK_EQUAL(max, 690);
}

BOOST_AUTO_TEST_CASE(GameManager_LevelProgressionTest)
{
    sf::RenderWindow window;
    Game game;
    AnimManager animManager;
    GameManager gm(window, &game, &animManager);

    int initialLevel = game.getLevel();
    gm.startNewLevel();

    BOOST_CHECK_EQUAL(game.getLevel(), initialLevel + 1);
}

BOOST_AUTO_TEST_CASE(GameManager_RemoveProjectilesTest)
{
    sf::RenderWindow window;
    Game game;
    AnimManager animManager;
    GameManager gm(window, &game, &animManager);
    PlayerProjectileFactory playerProjectileFactory;
    AlienProjectileFactory alienProjectileFactory;

    auto playerProjectile1 = playerProjectileFactory.createProjectile(400, 100);
    auto playerProjectile2 = playerProjectileFactory.createProjectile(400, -10);
    auto alienProjectile1 = alienProjectileFactory.createProjectile(400, 600);
    auto alienProjectile2 = alienProjectileFactory.createProjectile(400, 710);

    game.getPlayerProjectiles().push_back(playerProjectile1);
    game.getPlayerProjectiles().push_back(playerProjectile2);
    game.getAlienProjectiles().push_back(alienProjectile1);
    game.getAlienProjectiles().push_back(alienProjectile2);

    BOOST_CHECK_EQUAL(game.getPlayerProjectiles().size(), 2);
    BOOST_CHECK_EQUAL(game.getAlienProjectiles().size(), 2);

    gm.removeProjectiles();

    BOOST_CHECK_EQUAL(game.getPlayerProjectiles().size(), 1);
    BOOST_CHECK_EQUAL(game.getAlienProjectiles().size(), 1);

    BOOST_CHECK_EQUAL(game.getPlayerProjectiles().front()->getPositionY(), 100);
    BOOST_CHECK_EQUAL(game.getAlienProjectiles().front()->getPositionY(), 600);
}
BOOST_AUTO_TEST_CASE(GameManager_playerStatusTest)
{
    sf::RenderWindow window;
    Game game;
    AnimManager animManager;
    GameManager gm(window, &game, &animManager);

    BOOST_CHECK_EQUAL(gm.playerStatus(), 1);
}

BOOST_AUTO_TEST_SUITE_END()