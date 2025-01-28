#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Alien.h"
#include <memory>

class Game
{
    private:
        std::vector<std::shared_ptr<Alien>> alien_army;
        int score = 0;
        int level = 1;
    public:
        void createArmy();
        explicit Game();
        ~Game();
        std::vector<std::shared_ptr<Alien>>& getAlienArmy();
        int& getScore();
        int& getLevel();


};



#endif // GAME_H