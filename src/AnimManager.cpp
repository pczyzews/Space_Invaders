#include "AnimManager.h"
#include <iostream>



void AnimManager::loadTextures(const sf::Texture& pTexture, const sf::Texture& texture1, const sf::Texture& texture2, const sf::Texture& texture3) {
    playerTexture = pTexture;
    alienTexture1 = texture1;
    alienTexture2 = texture2;
    alienTexture3 = texture3;
}

void AnimManager::addPlayerAnimation(Player* player) {
    addAnimation(
        std::make_shared<Animation>(playerTexture, 16, 16, 2, 0.5f, true),
        player,
        player->getSizeX() / 16.0f,
        player->getSizeY() / 16.0f
    );
}

void AnimManager::addAlienAnimations(Game* game) {
    int alienCount = game->getAlienArmy().size();
    int quarter = alienCount / 4;
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
            alien.get(),
            alien->getSizeX() / 11.0f,
            alien->getSizeY() / 11.0f
        );

        ++index;
    }
}


void AnimManager::addAnimation(const std::shared_ptr<Animation>& animation, Entity* x, float scaleX, float scaleY) {
    animation->setReference(x);
    animation->setScale(scaleX, scaleY);
    animation->play();
    animations.push_back(animation);
    std::cout << "Dodano animację. Obecna liczba animacji: " << animations.size() << std::endl;

}

void AnimManager::updateAll(float deltaTime) {
    for (auto& animation : animations) {
        animation->update(deltaTime);
    }
}

void AnimManager::drawAll(sf::RenderWindow& window) {
    for (auto& animation : animations) {
        animation->draw(window);
    }
}

void AnimManager::removeAnimation(const std::shared_ptr<Animation>& animation) {
    //animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end());
    animation->stop();
}

void AnimManager::checkRemove(Entity* removed) {
    for (auto& animation : animations) {
        if (animation->getEntity() == removed) {
            removeAnimation(animation);
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