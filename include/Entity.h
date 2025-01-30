#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp> //potrzebne
#include <string>
#include <memory>
#include "Projectile.h"

class Entity
{
private:
    float sizeX;
    float sizeY;
    std::shared_ptr<float> positionX;
    std::shared_ptr<float> positionY;
    sf::Texture texture;
    sf::RectangleShape rect;
    int lives;

public:
    std::shared_ptr<float> getPositionXPtr() const { return positionX; }
    std::shared_ptr<float> getPositionYPtr() const { return positionY; }
    virtual std::shared_ptr<Projectile> shoot() = 0;
    float getPositionX() const;
    float getPositionY() const;
    float getSizeX() const;
    float getSizeY() const;
    Entity(float sizeX, float sizeY, float positionX, float positionY);
    virtual ~Entity();
    void setTexture(const std::string& texturePath);
    sf::RectangleShape& getRect();
    void updatePosition(float offsetX, float offsetY);
};

#endif // ENTITY_H
