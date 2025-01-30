#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
class Gamestate;

class Screen {
private:
    sf::RenderWindow* window;
    Gamestate* state;
public:
    Screen(sf::RenderWindow* window);
    void changeState(Gamestate* gamestate);
    void run(sf::Event &event) const;
};

#endif // SCREEN_H
