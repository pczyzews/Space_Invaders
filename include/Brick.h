#ifndef BRICK_H
#define BRICK_H
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Brick : public Entity {
    private:
    int hitCount = 3;

    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;

    public:
    Brick(float sizeX, float sizeY, float positionX, float positionY,  std::shared_ptr<sf::Texture> tex);
    ~Brick();

    void hit();
    bool isDestroyed() const;

    void updateTexture();
    void draw(sf::RenderWindow& window);
};



#endif //BRICK_H
