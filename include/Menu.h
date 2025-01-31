#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "GameState.h"

class Screen;

class Menu : public GameState {
private:
    sf::Font font;
    sf::Text startText;
    sf::Text loadText;
    Screen* screen;
public:
    explicit Menu(Screen* screen);
    std::shared_ptr<GameState> run(sf::Event& event, sf::RenderWindow* window) override;
};

#endif // MENU_H