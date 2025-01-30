#include "../include/Brick.h"


Brick::Brick(float sizeX, float sizeY, float positionX, float positionY, std::shared_ptr<sf::Texture> tex) : Entity(sizeX, sizeY, positionX, positionY), texture(std::move(tex)) {

    sprite.setTexture(*texture);
    sprite.setPosition(getPositionX(), getPositionY());
    updateTexture();

}
Brick::~Brick() =default;

void Brick::draw(sf::RenderWindow& window) {
    window.draw(sprite);

}

void Brick::hit() {
    if (hitCount > 0) {
        hitCount--;
        updateTexture();
    }
}

bool Brick::isDestroyed() const {
    return hitCount <= 0;
}

void Brick::updateTexture() {
    int textureY = (3 - hitCount) * 20;
    sprite.setTextureRect(sf::IntRect(textureY, 0, 10, 10));
    float scaleX = getSizeX() / 10.0f;
    float scaleY = getSizeY() / 10.0f;
    sprite.setScale(scaleX, scaleY);
}