#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <memory>

class Screen;

class GameOver : public GameState {
private:
    sf::Font font;
    sf::Text overText;
    sf::Text againText;
    Screen* screen;
public:
    GameOver();
    std::shared_ptr<GameState> run(sf::Event& event, sf::RenderWindow* window) override;
};

#endif // GAMEOVER_H
