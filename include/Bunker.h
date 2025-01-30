#ifndef BUNKER_H
#define BUNKER_H
#include <SFML/Graphics.hpp>
#include <memory>

class Bunker {
private:
    float sizeX;
    float sizeY;
    float positionX;
    float positionY;
    int hitCount = 3;

    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;

public:
    Bunker(float sizeX, float sizeY, float positionX, float positionY, std::shared_ptr<sf::Texture> tex);

    void hit();
    bool isDestroyed() const;

    void updateTexture();
    void draw(sf::RenderWindow& window) const;

    float getPositionX() const { return positionX; }
    float getPositionY() const { return positionY; }
    float getSizeX() const { return sizeX; }
    float getSizeY() const { return sizeY; }
};

#endif //BUNKER_H
