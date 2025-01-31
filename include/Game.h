#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <vector>

class Bunker;
class Projectile;
class Player;
class Alien;

using ProjectileVector = std::vector<std::shared_ptr<Projectile>>;
using AlienVector = std::vector<std::shared_ptr<Alien>>;
using BunkerVector = std::vector<std::shared_ptr<Bunker>>;

class Game {
    private:
        std::shared_ptr<Player> player;
        ProjectileVector alienProjectiles;
        ProjectileVector playerProjectiles;
        AlienVector alien_army;
        BunkerVector wall;
        std::shared_ptr<sf::Texture> brickTexture;
        int score = 0;
        int level = 1;
    public:
        void createArmy();
        explicit Game();
        ~Game();
        int getScore() const;
        int getLevel() const;
        void increaseScore(int inc);
        void increaseLevel(int inc);
        void startGame();
        void createWall();
        void clearWall();
        std::shared_ptr<Player>& getPlayer();
        ProjectileVector& getPlayerProjectiles();
        ProjectileVector& getAlienProjectiles();
        AlienVector& getAlienArmy();
        BunkerVector& getWall();
};

#endif // GAME_H