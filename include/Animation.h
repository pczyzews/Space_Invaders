#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
private:
    sf::Sprite sprite;                  // Sprite rysowany na ekranie
    std::vector<sf::IntRect> frames;    // Wektory prostokątów reprezentujących klatki animacji
    int currentFrame;                   // Indeks aktualnej klatki
    float frameDuration;                // Czas trwania jednej klatki (w sekundach)
    sf::Clock clock;                    // Zegar do kontrolowania czasu animacji
    bool loop;                          // Czy animacja jest zapętlona
    bool playing;                       // Czy animacja jest odtwarzana

public:
    // Konstruktor
    Animation(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop = true);

    // Ustawienie pozycji sprite'a
    void setPosition(float x, float y);

    // Ustawienie skali
    void setScale(float scaleX, float scaleY);

    // Ustawienie zapętlania animacji
    void setLoop(bool shouldLoop);

    // Rozpoczęcie animacji
    void play();

    // Zatrzymanie animacji
    void stop();

    // Reset animacji do pierwszej klatki
    void reset();

    // Aktualizacja animacji (wywoływana w głównej pętli gry)
    void update();

    // Rysowanie animacji na ekranie
    void draw(sf::RenderWindow& window);
};

#endif // ANIMATION_H