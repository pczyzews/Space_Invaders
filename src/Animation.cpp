#include "Animation.h"
#include <iostream>

Animation::Animation(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop)
    : currentFrame(0), frameDuration(frameDuration), loop(loop), playing(false) {
    // Ustawienie sprite'a
    sprite.setTexture(texture);

    // Wyliczanie klatek
    for (int i = 0; i < frameCount; ++i) {
        frames.emplace_back(i * frameWidth, 0, frameWidth, frameHeight);
    }

    // Ustawienie początkowej klatki
    sprite.setTextureRect(frames[0]);

    std::cout << "Wczytano klatki animacji:" << std::endl;
    for (const auto& frame : frames) {
        std::cout << "Frame: " << frame.left << ", " << frame.top << ", " << frame.width << ", " << frame.height << std::endl;
    }
}

void Animation::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    std::cout << "Pozycja sprite: (" << x << ", " << y << ")" << std::endl;

}

void Animation::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
    std::cout << "Skala sprite: (" << scaleX << ", " << scaleY << ")" << std::endl;
}

void Animation::setLoop(bool shouldLoop) {
    loop = shouldLoop;
}

void Animation::play() {
    playing = true;
}

void Animation::stop() {
    playing = false;
}

void Animation::reset() {
    currentFrame = 0;
    sprite.setTextureRect(frames[0]);
    clock.restart();
}

void Animation::update() {
    if (!playing) return;

    if (clock.getElapsedTime().asSeconds() > frameDuration) {
        currentFrame = (currentFrame + 1) % frames.size();
        std::cout << "Aktualna klatka: " << currentFrame << std::endl;

        if (!loop && currentFrame == 0) {
            stop();
            return;
        }

        sprite.setTextureRect(frames[currentFrame]);
        clock.restart();
    }
}

void Animation::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
