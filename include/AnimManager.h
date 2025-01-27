#ifndef ANIMMANAGER_H
#define ANIMMANAGER_H
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.h"



class AnimManager {
private:
    std::vector<std::shared_ptr<Animation>> animations;
public:
    void addAnimation(const std::shared_ptr<Animation>& animation, float* x, float* y, float scaleX, float scaleY);
    void updateAll(float deltaTime);
    void drawAll(sf::RenderWindow& window);
    void removeAnimation(const std::shared_ptr<Animation>& animation);
};



#endif //ANIMMANAGER_H
