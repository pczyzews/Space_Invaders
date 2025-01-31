#include <boost/test/unit_test.hpp>
#include "Screen.h"
#include "Menu.h"
#include "Play.h"
#include "GameOver.h"
#include <SFML/Graphics.hpp>
#include <memory>

BOOST_AUTO_TEST_SUITE(TestScreen)

BOOST_AUTO_TEST_CASE(ScreenInitializationTest)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    Screen screen(&window);

    std::shared_ptr<Gamestate> initialState = std::make_shared<Menu>(&screen);
    BOOST_CHECK(typeid(*initialState) == typeid(Menu));
}

BOOST_AUTO_TEST_CASE(PushStateTest)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    Screen screen(&window);

    std::shared_ptr<Gamestate> playState = std::make_shared<Play>();
    screen.pushState(playState);

    BOOST_CHECK(typeid(*playState) == typeid(Play));
}

BOOST_AUTO_TEST_CASE(MenuToPlayTransitionTest)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    Screen screen(&window);

    std::shared_ptr<Gamestate> playState = std::make_shared<Play>();
    screen.pushState(playState);

    BOOST_CHECK(typeid(*playState) == typeid(Play));
}

BOOST_AUTO_TEST_CASE(PlayToGameOverTransitionTest)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    Screen screen(&window);

    std::shared_ptr<Gamestate> playState = std::make_shared<Play>();
    screen.pushState(playState);

    std::shared_ptr<Gamestate> gameOverState = std::make_shared<GameOver>();
    screen.pushState(gameOverState);

    BOOST_CHECK(typeid(*gameOverState) == typeid(GameOver));
}

BOOST_AUTO_TEST_SUITE_END()