#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <memory>

class Gamestate {
public:
    virtual ~Gamestate() = default;
    virtual std::shared_ptr<Gamestate> run(sf::Event &event, sf::RenderWindow* window) = 0;
};

#endif // GAMESTATE_H
