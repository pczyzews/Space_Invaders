#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Player.h"
#include <thread>
#include <chrono>
#include "Game.h"

class GameManager {
private:
    bool isRunning;
    float alien_step = 10.0f;
    float min_alien_position = 100;
    float max_alien_position = 660;
    bool check_army_movement_down = false;
    float army_move_per_second = 1000;
    std::chrono::time_point<std::chrono::steady_clock> lastMoveTime;
    Player* player;
public:
    GameManager(Player* p);
    ~GameManager();
    void handleInput();
    void movingAlienArmy(Game &game);
    void CalculateMaxPositions(float& min, float& max, Game& game);
};

#endif // GAMEMANAGER_H
