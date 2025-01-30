#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include <stack>
#include <memory>

class Screen {
private:
    sf::RenderWindow* window;
    std::stack<std::shared_ptr<Gamestate>> stateStack;

public:
    Screen(sf::RenderWindow* window);
    void pushState(std::shared_ptr<Gamestate> newstate);
    void popState();
    void run(sf::Event &event);
};

#endif // SCREEN_H