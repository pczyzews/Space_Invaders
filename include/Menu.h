#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "Gamestate.h"

class Screen;

class Menu : public Gamestate {
private:
    sf::Font font;
    sf::Text startText;
    sf::Text loadText;
    Screen* screen;

public:
    Menu(Screen* screen);
    std::shared_ptr<Gamestate> run(sf::Event& event, sf::RenderWindow* window) override;
};

#endif // MENU_H