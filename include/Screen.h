#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include "Gamestate.h"

class Screen {
private:
    sf::RenderWindow* window;
    Gamestate* state;
public:
    Screen(sf::RenderWindow* window);
    void changeState(Gamestate* gamestate);
    void run(sf::Event &event);
};

#endif // SCREEN_H
