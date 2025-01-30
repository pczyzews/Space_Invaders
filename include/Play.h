#ifndef PLAY_H
#define PLAY_H
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
class Play : public Gamestate
{
public:
    Play();
    std::shared_ptr<Gamestate> run(sf::Event& event, sf::RenderWindow* window) override;
};

#endif // PLAY_H
