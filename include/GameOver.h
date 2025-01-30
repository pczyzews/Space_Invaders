#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <SFML/Graphics.hpp>
#include "Play.h"
#include "Screen.h"
#include <memory>

class GameOver : public Gamestate {
private:
    sf::Font font;
    sf::Text overText;
    sf::Text againText;
    Screen* screen;

public:
    GameOver();
    std::shared_ptr<Gamestate> run(sf::Event& event, sf::RenderWindow* window) override;
};

#endif // GAMEOVER_H
