#include "AnimManager.h"
#include "Animation.h"
#include "Player.h"
#include "Game.h"
#include "Alien.h"
#include <iostream>

void AnimManager::loadTextures(const sf::Texture& pTexture, const sf::Texture& texture1, const sf::Texture& texture2, const sf::Texture& texture3, const sf::Texture& bTexture) {
    playerTexture = pTexture;
    alienTexture1 = texture1;
    alienTexture2 = texture2;
    alienTexture3 = texture3;
    boomTexture = bTexture;
}

void AnimManager::addPlayerAnimation(const std::shared_ptr<Player>& player) {
    addAnimation(
        std::make_shared<Animation>(playerTexture, 16, 16, 2, 0.5f, true),
        player,
        player->getSizeX() / 16.0f,
        player->getSizeY() / 16.0f
    );
}

void AnimManager::addAlienAnimations(Game* game) {
    unsigned const long alienCount = game->getAlienArmy().size();
    unsigned const int quarter = alienCount / 4;
    int index = 0;

    for (const auto& alien : game->getAlienArmy()) {
        const sf::Texture* currentTexture = nullptr;

        if (index < quarter) {
            currentTexture = &alienTexture1;
        } else if (index < 2 * quarter) {
            currentTexture = &alienTexture2;
        } else {
            currentTexture = &alienTexture3;
        }

        addAnimation(
            std::make_shared<Animation>(*currentTexture, 11, 11, 2, 0.3f, true),
            alien,
            alien->getSizeX() / 11.0f,
            alien->getSizeY() / 11.0f
        );

        ++index;
    }
}

void AnimManager::addAnimation(const std::shared_ptr<Animation>& animation, const std::shared_ptr<Entity>& x, const float scaleX, const float scaleY) {
    animation->setReference(x);
    animation->setScale(scaleX, scaleY);
    animation->play();
    animations.push_back(animation);
}

void AnimManager::updateAll(const float deltaTime) {
    for (const auto& animation : animations) {
        animation->update(deltaTime);
    }
}

void AnimManager::drawAll(sf::RenderWindow& window) const {
    for (const auto& animation : animations) {
        animation->draw(window);
    }
}

void AnimManager::checkRemove(std::shared_ptr<Entity> const &removed) {
    for (const auto& animation : animations) {
        if (animation->getEntity() == removed) {
            animation->stop();
        }
    }
}

void AnimManager::clearAnimations() {
    animations.clear();
}

const sf::Texture& AnimManager::getAlienTexture1() const {
    return alienTexture1;
}

const sf::Texture& AnimManager::getAlienTexture2() const {
    return alienTexture2;
}

const sf::Texture& AnimManager::getAlienTexture3() const {
    return alienTexture3;
}

const sf::Texture& AnimManager::getPlayerTexture() const {
    return playerTexture;
}

const sf::Texture& AnimManager::getBoomTexture() const {
    return boomTexture;
}

void AnimManager::collisionAnimation(const float x, const float y, const float sizeX, const float sizeY) {
    float frameWidth = 16;
    float frameHeight = 16;
    int frameCount = 15;
    float frameDuration = 0.05f;
    bool loop = false;
    const auto explosionAnimation = std::make_shared<Animation>(boomTexture, frameWidth, frameHeight, frameCount, frameDuration, loop);

    explosionAnimation->setPosition(x, y);
    explosionAnimation->setScale(sizeX/frameWidth, sizeY/frameHeight);
    explosionAnimation->play();
    animations.push_back(explosionAnimation);
}