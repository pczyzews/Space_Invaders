#include "Animation.h"
#include "Entity.h"

Animation::Animation(const sf::Texture& texture, const int frameWidth, const int frameHeight, const int frameCount, const float frameDuration, const bool loop)
    : currentFrame(0), frameDuration(frameDuration), loop(loop), playing(false) {
    sprite.setTexture(texture);

    for (int i = 0; i < frameCount; ++i) {
        frames.emplace_back(i * frameWidth, 0, frameWidth, frameHeight);
    }
    sprite.setTextureRect(frames[0]);
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

void Animation::setScale(const float scaleX, const float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void Animation::setLoop(const bool shouldLoop) {
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

void Animation::update(const float deltaTime) {
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

void Animation::setPosition(const float x, const float y) {
    sprite.setPosition(x, y);
}