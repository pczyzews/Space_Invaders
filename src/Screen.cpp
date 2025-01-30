#include "Screen.h"
#include "Menu.h"

Screen::Screen(sf::RenderWindow* window) : window(window)
{
    this->state = new Menu(this);
}

void Screen::run(sf::Event& event) const
{
    this->state->run(event, window);
}

void Screen::changeState(Gamestate* newstate)
{
    delete this->state;
    this->state = newstate;
}
