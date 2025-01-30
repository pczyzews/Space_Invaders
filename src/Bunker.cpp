// #include "Bunker.h"
//
// #include "Brick.h"
//
//
// Bunker::Bunker(float sizeX, float sizeY, float positionX, float positionY) : Entity(sizeX, sizeY, positionX, positionY) {
// }
// Bunker::~Bunker() =default;
//
// void Bunker::draw(sf::RenderWindow& window) {
//     window.draw(getRect());
// }
//
// void Bunker::createWall() {
//     for (int j = 0; j < 3; j++) {
//         for (int i = 0; i < 10; i++) {
//             wall.push_back(std::make_shared<Brick>(20, 20, 100 + 20 * i, 400 + 20 * j));
//         }
//     }
// }
//
// std::vector<std::shared_ptr<Brick>>& Bunker::getWall()
// {
//     return wall;
// }