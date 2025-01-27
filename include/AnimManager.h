#ifndef ANIMMANAGER_H
#define ANIMMANAGER_H
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Game.h"



class AnimManager {
private:
    std::vector<std::shared_ptr<Animation>> animations;
public:
    void loadAnimations(Player& player, Game& game);
    void addAnimation(const std::shared_ptr<Animation>& animation, Entity* x, float scaleX, float scaleY);
    void updateAll(float deltaTime);
    void drawAll(sf::RenderWindow& window);
    void removeAnimation(const std::shared_ptr<Animation>& animation);
    void checkRemove(Entity* removed);
    //void removeAnimationByOwner(Entity* owner);

};



#endif //ANIMMANAGER_H
