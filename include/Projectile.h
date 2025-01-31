#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <memory>
#include <SFML/Graphics.hpp>

class Projectile {
private:
    float sizeX = 10;
    float sizeY = 20;
    std::shared_ptr<float> positionX;
    std::shared_ptr<float> positionY;
    sf::Texture texture;
    sf::RectangleShape rect;
public:
    Projectile(float positionX, float positionY);
    virtual ~Projectile();
    void draw(sf::RenderWindow& window);
    virtual void updatePosition() = 0;
    void setPositionX(float x) const;
    void setPositionY(float y) const;
    float getPositionX() const;
    float getPositionY() const;
    float getSizeX() const;
    float getSizeY() const;
    void setTexture(const std::string& texturePath);
    sf::RectangleShape& getRect();
};

#endif //PROJECTILE_H
