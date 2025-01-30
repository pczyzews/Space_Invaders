#include "Screen.h"
#include "Menu.h"

Screen::Screen(sf::RenderWindow* window) : window(window) {
    pushState(std::make_shared<Menu>(this));
}

void Screen::run(sf::Event& event) {
    while (!stateStack.empty() && window->isOpen()) {
        std::shared_ptr<Gamestate> newState = stateStack.top()->run(event, window);
        if (newState) {
            pushState(newState);
        }
    }
}

void Screen::pushState(std::shared_ptr<Gamestate> newstate) {
    stateStack.push(newstate);
}

void Screen::popState() {
    if (!stateStack.empty()) {
        stateStack.pop();
    }
}