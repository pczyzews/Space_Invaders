#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <memory>

class GameState {
public:
    virtual ~GameState() = default;
    virtual std::shared_ptr<GameState> run(sf::Event &event, sf::RenderWindow* window) = 0;
};

#endif // GAMESTATE_H
