#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 700), "Space Invaders", sf::Style::Close);

    Player test(100, 100, 100, 300);
    Projectile* player_bullet = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            test.getRect().move(0.3, 0.0);
            test.updatePosition(0.3, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            test.getRect().move(-0.3, 0.0);
            test.updatePosition(-0.3, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player_bullet == nullptr)
        {
            player_bullet = new Projectile(10, 20, test.getPositionX() + 45, test.getPositionY(), true);
        }

        if (player_bullet != nullptr)
        {
            player_bullet->getRect().move(0, -5);
            player_bullet->updatePosition(0, -5);

            if (player_bullet->getPositionY() + player_bullet->getRect().getSize().y < 0)
            {
                delete player_bullet;
                player_bullet = nullptr;
            }
        }

        window.clear();
        window.draw(test.getRect());
        if (player_bullet != nullptr)
        {
            window.draw(player_bullet->getRect());
        }
        window.display();
    }

    if (player_bullet != nullptr)
    {
        delete player_bullet;
    }

    return 0;
}
