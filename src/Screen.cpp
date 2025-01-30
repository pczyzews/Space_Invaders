#include "Screen.h"

#include "GameOver.h"
#include "Menu.h"

Screen::Screen(sf::RenderWindow* window) : window(window)
{
    this->state = new GameOver(this);
}

void Screen::run(sf::Event& event)
{
    this->state->run(event, window);
}

void Screen::changeState(Gamestate* newstate)
{
    delete this->state;
    this->state = newstate;
}
