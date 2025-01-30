#include "Bunker.h"

Bunker::Bunker(float sizeX, float sizeY, float positionX, float positionY, std::shared_ptr<sf::Texture> tex)
    : sizeX(sizeX), sizeY(sizeY), positionX(positionX), positionY(positionY), texture(std::move(tex)) {
    sprite.setTexture(*texture);
    sprite.setPosition(positionX, positionY);
    updateTexture();
}

void Bunker::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Bunker::hit() {
    if (hitCount > 0) {
        hitCount--;
        updateTexture();
    }
}

bool Bunker::isDestroyed() const {
    return hitCount <= 0;
}

void Bunker::updateTexture() {
    int textureY = (3 - hitCount) * 20;
    sprite.setTextureRect(sf::IntRect(textureY, 0, 10, 10));
    float scaleX = sizeX / 10.0f;
    float scaleY = sizeY / 10.0f;
    sprite.setScale(scaleX, scaleY);
}
