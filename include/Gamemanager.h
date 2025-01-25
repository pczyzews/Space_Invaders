#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Player.h"

class GameManager {
private:
    bool isRunning;
    Player* player;
public:
    GameManager(Player* p);
    ~GameManager();
    void handleInput();
};

#endif // GAMEMANAGER_H
