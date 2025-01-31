#ifndef PLAY_H
#define PLAY_H
#include <SFML/Graphics.hpp>
#include "GameState.h"

class Play : public GameState {
public:
    Play();
    std::shared_ptr<GameState> run(sf::Event& event, sf::RenderWindow* window) override;
};

#endif // PLAY_H