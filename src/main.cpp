#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Gamemanager.h"
#include "Alien.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);


    window.setFramerateLimit(144);

    Player test(64, 64, 300, 500);
    Projectile* player_bullet = nullptr;
    Game game;
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
            if (event.type == sf::Event::Resized)
            {
                window.setSize(sf::Vector2u(800, 700));
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

        manager.movingAlienArmy(game);

        window.clear();
        window.draw(test.getRect());
        if (player_bullet != nullptr)
        {
            window.draw(player_bullet->getRect());
        }
            for (const auto& alien : game.getAlienArmy())
            {
                window.draw(alien->getRect());
            }
        window.display();
        }

    }
