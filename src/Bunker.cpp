#include "Bunker.h"

Bunker::Bunker(const float sizeX, const float sizeY, const float positionX, const float positionY, std::shared_ptr<sf::Texture> tex)
    : sizeX(sizeX), sizeY(sizeY), positionX(positionX), positionY(positionY), texture(std::move(tex)) {
    sprite.setTexture(*texture);
    sprite.setPosition(positionX, positionY);
    updateTexture();
}

void Bunker::draw(sf::RenderWindow& window) const {
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
    const int textureY = (3 - hitCount) * 20;
    sprite.setTextureRect(sf::IntRect(textureY, 0, 10, 10));
    const float scaleX = sizeX / 10.0f;
    const float scaleY = sizeY / 10.0f;
    sprite.setScale(scaleX, scaleY);
}