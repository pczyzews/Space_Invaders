#ifndef PLAY_H
#define PLAY_H
#include <SFML/Graphics.hpp>
#include "Gamestate.h"
#include "Player.h"

class Alien;
class Projectile;

class Play : public Gamestate
{
public:
    Play();
    void run(sf::Event& event, sf::RenderWindow* window) override;
};

#endif // PLAY_H
