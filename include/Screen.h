#ifndef SCREEN_H
#define SCREEN_H
#include <memory>
#include <SFML/Graphics.hpp>
class Gamestate;

class Screen {
private:
    sf::RenderWindow* window;
    Gamestate* state;
public:
    Screen(sf::RenderWindow* window);
    void pushState(std::shared_ptr<Gamestate> newstate);
    void popState();
    void run(sf::Event &event);
};

#endif // SCREEN_H
