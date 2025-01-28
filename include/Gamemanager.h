#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Game.h"
#include "Animation.h"
#include "AnimManager.h"
#include <thread>
#include <chrono>


class Player;

class GameManager {
private:
    bool isRunning;
    float alien_step = 10.0f;
    float min_alien_position = 100;
    float max_alien_position = 660;
    bool check_army_movement_down = false;
    float army_move_per_second = 1000;

    sf::Font font;
    sf::Text scoreText;
    sf::Text levelText;
    sf::Texture heartTexture;
    sf::Sprite heartSprite;
    std::chrono::time_point<std::chrono::steady_clock> lastMoveTime;
    Player* player;
    Game* game;
    AnimManager* animationManager;
    sf::RenderWindow& window;

    std::vector<std::shared_ptr<Animation>> animations;

public:
    GameManager(sf::RenderWindow& window, Player* p, Game* g, AnimManager* animManager);
    ~GameManager();
    void handleInput();
    void movingAlienArmy(Game &game);
    void CalculateMaxPositions(float& min, float& max, Game& game);
    void checkForCollision(Game& game, Player& player);
    void startNewLevel();
    void drawLvlScore();
    void drawLives();
    void render();

};

#endif // GAMEMANAGER_H
