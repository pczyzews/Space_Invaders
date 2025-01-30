#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Alien.h"
#include <memory>

#include "Bunker.h"
#include "Player.h"

class Game
{
    private:
        std::shared_ptr<Player> player;
        std::vector<std::shared_ptr<Projectile>> alienProjectiles;
        std::vector<std::shared_ptr<Projectile>> playerProjectiles;
        std::vector<std::shared_ptr<Alien>> alien_army;
        std::vector<std::shared_ptr<Bunker>> wall;
        std::shared_ptr<sf::Texture> brickTexture;
        int score = 0;
        int level = 1;
    public:
        void createArmy();
        explicit Game();
        ~Game();
        int& getScore();
        int& getLevel();
        void startGame();
        void createWall();
        void clearWall();
        std::shared_ptr<Player>& getPlayer();
        std::vector<std::shared_ptr<Projectile>>& getPlayerProjectiles();
        std::vector<std::shared_ptr<Projectile>>& getAlienProjectiles();
        std::vector<std::shared_ptr<Alien>>& getAlienArmy();
        std::vector<std::shared_ptr<Bunker>>& getWall();



};



#endif // GAME_H