#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>

class Gamestate{
public:
    virtual void run(sf::Event &event, sf::RenderWindow* window) = 0;
};

#endif // GAMESTATE_H
