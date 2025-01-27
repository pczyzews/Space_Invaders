#include "AnimManager.h"
#include <iostream>

void AnimManager::loadAnimations(Player& player, Game& game) {
    sf::Texture playerTexture;
    playerTexture.loadFromFile("../textures/2player.png");

    addAnimation(
        std::make_shared<Animation>(playerTexture, 16, 16, 2, 0.5f, true),
        player.getPositionXPtr(),
        player.getPositionYPtr(),
        player.getSizeX() / 16.0f,
        player.getSizeY() / 16.0f
    );

    sf::Texture alienTexture1;
    alienTexture1.loadFromFile("../textures/2alien1.png");
    sf::Texture alienTexture2;
    alienTexture2.loadFromFile("../textures/2alien2.png");
    sf::Texture alienTexture3;
    alienTexture3.loadFromFile("../textures/2alien3.png");

    int alienCount = game.getAlienArmy().size();
    int quarter = alienCount / 4;
    int index = 0;

    // Dodawanie animacji dla obcych
    for (const auto& alien : game.getAlienArmy()) {
        const sf::Texture* currentTexture = nullptr;

        // Wybór tekstury dla obcych
        if (index < quarter) {
            currentTexture = &alienTexture1;
        } else if (index < 2 * quarter) {
            currentTexture = &alienTexture2;
        } else {
            currentTexture = &alienTexture3;
        }

        // Dodawanie animacji dla obcego
        addAnimation(
            std::make_shared<Animation>(
                *currentTexture, 11, 11, 2, 0.3f, true
            ),
            alien->getPositionXPtr(),
            alien->getPositionYPtr(),
            alien->getSizeX() / 11.0f,
            alien->getSizeY() / 11.0f
        );

        ++index; // Zwiększenie indeksu
    }
}

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
