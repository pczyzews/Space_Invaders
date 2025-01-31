#include <boost/test/unit_test.hpp>
#include "Game.h"

BOOST_AUTO_TEST_SUITE(TestGame)

BOOST_AUTO_TEST_CASE(GameInitializationTest)
{
    Game game;

    BOOST_TEST(game.getLevel() == 1);
    BOOST_TEST(game.getScore() == 0);
    BOOST_TEST(game.getAlienArmy().empty() == false);
    BOOST_TEST(game.getWall().empty() == false);
    BOOST_TEST(game.getPlayer() != nullptr);
}

BOOST_AUTO_TEST_CASE(IncreaseLevelTest)
{
    Game game;
    game.increaseLevel(2);
    BOOST_TEST(game.getLevel() == 3);
}

BOOST_AUTO_TEST_CASE(IncreaseScoreTest)
{
    Game game;
    game.increaseScore(50);
    BOOST_TEST(game.getScore() == 50);
}

BOOST_AUTO_TEST_CASE(AlienArmySizeTest)
{
    Game game;
    BOOST_TEST(game.getAlienArmy().size() == 60);
}

BOOST_AUTO_TEST_CASE(PlayerProjectilesTest)
{
    Game game;
    BOOST_TEST(game.getPlayerProjectiles().empty());
}

BOOST_AUTO_TEST_CASE(AlienProjectilesTest)
{
    Game game;
    BOOST_TEST(game.getAlienProjectiles().empty());
}

BOOST_AUTO_TEST_CASE(WallClearingTest)
{
    Game game;
    BOOST_TEST(game.getWall().empty() == false);

    game.clearWall();
    BOOST_TEST(game.getWall().empty() == true);
}

BOOST_AUTO_TEST_SUITE_END()