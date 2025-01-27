#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Entity;

class Animation {
private:
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    std::size_t currentFrame = 0;
    float frameDuration;
    float elapsedTime = 0.0f;
    bool loop;
    bool playing;
    float* positionX = nullptr;
    float* positionY = nullptr;
    Entity* entity;

public:
    Animation(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop = true);
    ~Animation();

    //void setPositionReference(float* x, float* y);
    void setReference(Entity* x);
    void setScale(float scaleX, float scaleY);
    void setLoop(bool shouldLoop);
    void play();
    void stop();
    void reset();
    Entity* getEntity();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
};

#endif // ANIMATION_H