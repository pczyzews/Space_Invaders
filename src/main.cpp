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

void CalculateMaxPositions(float& min, float& max, const vector<Alien*>& aliens)
{
    min = 9999;
    max = -1;
    for (Alien* alien : aliens)
    {
        if (alien->getPositionX() < min)
        {
            min = alien->getPositionX();
        }
        if (alien->getPositionX() + 30 > max)
        {
            max = alien->getPositionX() + 30;
        }
    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Space Invaders", sf::Style::Close);
    window.setFramerateLimit(144);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("../textures/2player.png");

    if (playerTexture.loadFromFile("../textures/2player.png")) {
        std::cerr << "Udało się załadować teksturę!" << std::endl;
    }

    Player test(64, 64, 368, 600, playerTexture, 16, 16,2 ,0.5);
    GameManager manager(&test);
    vector<Alien*> aliens;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 15; i++)
        {
            aliens.push_back(new Alien(30, 30, 100 + 40 * i, 100 + 40 * j));
        }
    }

    float alien_speed = 10.0f;
    float min_alien_position = 100;
    float max_alien_position = 660;
    bool check_army_movement_down = false;
    float army_move_per_second = 1000;

    auto lastMoveTime = chrono::steady_clock::now();

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

            auto currentTime = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(currentTime - lastMoveTime).count() >= army_move_per_second)
            {
                if ((min_alien_position <= 10 || max_alien_position >= 790) && check_army_movement_down == false)
                {
                    for (Alien* alien : aliens)
                    {
                        alien->getRect().move(0, 10);
                        alien->updatePosition(0, 10);
                    }
                    alien_speed = -alien_speed;
                    check_army_movement_down = true;
                    if (army_move_per_second >= 300)
                    {
                        army_move_per_second -= 100;
                    }
                }
                else
                {
                    for (Alien* alien : aliens)
                    {
                        alien->getRect().move(alien_speed, 0);
                        alien->updatePosition(alien_speed, 0);
                    }
                    check_army_movement_down = false;

                }

                CalculateMaxPositions(min_alien_position, max_alien_position, aliens);
                printf("Min: %f, Max: %f, Speed: %f, Army move per second: %f\n", min_alien_position, max_alien_position, alien_speed, army_move_per_second);
                lastMoveTime = currentTime;

            }

        manager.handleInput();
        window.clear();
        //window.draw(test.getRect());
            test.update();
            test.draw(window);
            for (Alien* alien : aliens)
                {
                    window.draw(alien->getRect());
                }

        window.display();
        }
        for (Alien* alien : aliens)
        {
            delete alien;
        }
    }
