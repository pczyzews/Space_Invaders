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
    sf::Texture playerTexture, alienTexture1, alienTexture2, alienTexture3;

public:
    const sf::Texture& getPlayerTexture() const;
    const sf::Texture& getAlienTexture1() const;
    const sf::Texture& getAlienTexture2() const;
    const sf::Texture& getAlienTexture3() const;

    void clearAnimations();

    void addPlayerAnimation(Player* player);

    void addAlienAnimations(Game* game);


    void addAnimation(const std::shared_ptr<Animation>& animation, Entity* x, float scaleX, float scaleY);
    void updateAll(float deltaTime);
    void drawAll(sf::RenderWindow& window);
    void removeAnimation(const std::shared_ptr<Animation>& animation);
    void checkRemove(Entity* removed);

    void loadTextures(const sf::Texture& pTexture, const sf::Texture& texture1, const sf::Texture& texture2, const sf::Texture& texture3);


};

#endif //ANIMMANAGER_H
