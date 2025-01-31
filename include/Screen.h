#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <stack>
#include <memory>

using Stack = std::stack<std::shared_ptr<GameState>>;

class Screen {
private:
    sf::RenderWindow* window;
    Stack stateStack;
public:
    explicit Screen(sf::RenderWindow* window);
    void pushState(const std::shared_ptr<GameState>& newState);
    void popState();
    void run(sf::Event &event);
};

#endif // SCREEN_H