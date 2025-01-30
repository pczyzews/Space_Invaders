#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Alien.h"
#include "Brick.h"
#include <memory>

class Game
{
    private:
    std::vector<std::shared_ptr<Alien>> alien_army;
    std::vector<std::shared_ptr<Brick>> wall;
    std::shared_ptr<sf::Texture> brickTexture;
    public:
    int score = 0;
    int level = 1;

    explicit Game();
    ~Game();
    void createArmy();
    std::vector<std::shared_ptr<Alien>>& getAlienArmy();
    void createWall();
    std::vector<std::shared_ptr<Brick>>& getWall();
    void clearWall();


};



#endif // GAME_H