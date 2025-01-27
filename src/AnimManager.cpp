#include "AnimManager.h"
#include <iostream>



void AnimManager::addAnimation(const std::shared_ptr<Animation>& animation, float* x, float* y, float scaleX, float scaleY) {
    animation->setPositionReference(x, y);
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
    animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end());
}
