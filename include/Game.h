#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Alien.h"
#include <memory>

#include "Player.h"

class Game
{
    private:
        std::shared_ptr<Player> player;
        std::vector<std::shared_ptr<Projectile>> alienProjectiles;
        std::vector<std::shared_ptr<Projectile>> playerProjectiles;
        std::vector<std::shared_ptr<Alien>> alien_army;
        int score = 0;
        int level = 1;
    public:
        void createArmy();
        explicit Game();
        ~Game();
        int& getScore();
        int& getLevel();
        void startGame();
        std::shared_ptr<Player>& getPlayer();
        std::vector<std::shared_ptr<Projectile>>& getPlayerProjectiles();
        std::vector<std::shared_ptr<Projectile>>& getAlienProjectiles();
        std::vector<std::shared_ptr<Alien>>& getAlienArmy();


};



#endif // GAME_H