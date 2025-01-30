#include "Animation.h"
#include <iostream>
#include "Entity.h"


Animation::Animation(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop)
    : currentFrame(0), frameDuration(frameDuration), loop(loop), playing(false) {
    sprite.setTexture(texture);

    for (int i = 0; i < frameCount; ++i) {
        frames.emplace_back(i * frameWidth, 0, frameWidth, frameHeight);
    }

    sprite.setTextureRect(frames[0]);

    std::cout << "Wczytano klatki animacji:" << std::endl;
    for (const auto& frame : frames) {
        std::cout << "Frame: " << frame.left << ", " << frame.top << ", " << frame.width << ", " << frame.height << std::endl;
    }
}

Animation::~Animation() = default;


void Animation::setReference(std::shared_ptr<Entity>const& x) {
    entity = x;
    positionX = x->getPositionXPtr();
    positionY = x->getPositionYPtr();
    if (positionX && positionY) {
        sprite.setPosition(*positionX, *positionY);
    }
}

void Animation::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
    std::cout << "Skala sprite: (" << scaleX << ", " << scaleY << ")" << std::endl;
}

void Animation::setLoop(bool shouldLoop) {
    loop = shouldLoop;
}

void Animation::play() {
    playing = true;
}

void Animation::stop() {
    playing = false;
}

std::shared_ptr<Entity> Animation::getEntity() {
    return entity;
}

void Animation::reset() {
    currentFrame = 0;
    sprite.setTextureRect(frames[0]);
    elapsedTime = 0.0f;
}

void Animation::update(float deltaTime) {
    if (!playing) return;


    if (positionX && positionY) {
        sprite.setPosition(*positionX, *positionY);
    }
    elapsedTime += deltaTime;

    if (elapsedTime > frameDuration) {
        elapsedTime -= frameDuration;
        currentFrame = (currentFrame + 1) % frames.size();

        if (!loop && currentFrame == 0) {
            stop();
            return;
        }

        sprite.setTextureRect(frames[currentFrame]);
    }
}

void Animation::draw(sf::RenderWindow& window) const
{
    if (!playing) return;
    window.draw(sprite);
}

void Animation::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

