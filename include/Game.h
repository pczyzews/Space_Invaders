#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Alien.h"
#include <memory>

class Game
{
    private:
        std::vector<std::shared_ptr<Alien>> alien_army;
    public:
        explicit Game();
        ~Game();
        std::vector<std::shared_ptr<Alien>>& getAlienArmy();


};



#endif // GAME_H