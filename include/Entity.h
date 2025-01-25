#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class Entity
{
private:
    float sizeX;
    float sizeY;
    float positionX;
    float positionY;
    sf::Texture texture;
    sf::RectangleShape rect;

public:
    float getPositionX() const;
    float getPositionY() const;
    float getSizeX() const;
    float getSizeY() const;
    float getSpeed();
    Entity(float sizeX, float sizeY, float positionX, float positionY);
    virtual ~Entity();
    void setTexture(const std::string& texturePath);
    sf::RectangleShape& getRect();
    void updatePosition(float offsetX, float offsetY);
};

#endif // ENTITY_H
