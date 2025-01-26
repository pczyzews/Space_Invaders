#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Gamemanager.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Space Invaders", sf::Style::Close);
    window.setFramerateLimit(144);

    Player test(64, 64, 300, 500);
    Projectile* player_bullet = nullptr;
    GameManager manager(&test);

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

        manager.handleInput();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player_bullet == nullptr)
        {
            player_bullet = new Projectile(10, 20, test.getPositionX() + 27, test.getPositionY(), true);
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
