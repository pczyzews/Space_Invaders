#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <chrono>
#include "Game.h"
#include "SFML/Graphics.hpp"

class CollisionDetector;
class AnimManager;
class Player;
class Animation;

class GameManager {
private:
    bool isRunning;
    float alien_step = 10.0f;
    float min_alien_position = 100;
    float max_alien_position = 660;
    bool check_army_movement_down = false;
    float army_move_per_second = 700;
    bool alienArmyLockedHorizontal = false;

    sf::Font font;
    sf::Text scoreText;
    sf::Text levelText;
    sf::Texture heartTexture;
    sf::Sprite heartSprite;
    std::chrono::time_point<std::chrono::steady_clock> lastMoveTime;
    Game* game;
    AnimManager* animationManager;

    CollisionDetector* collisionDetector;

    sf::RenderWindow& window;

    std::vector<std::shared_ptr<Animation>> animations;

public:
    GameManager(sf::RenderWindow& window, Game* g, AnimManager* animManager);
    ~GameManager();
    void handleInput() const;
    void drawBunkers() const;
    void movingAlienArmy(Game &game);
    static void calculateMaxPositions(float& min, float& max, Game& game);
    void startNewLevel();
    void drawLvlScore();
    void drawLives();
    void removeProjectiles() const;
    void updateProjectiles() const;
    void render();
    void updateCollisions();
    void drawProjectiles(sf::RenderWindow& window) const;
};

#endif // GAMEMANAGER_H
