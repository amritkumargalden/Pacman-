#ifndef GHOST_H
#define GHOST_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Ghost {
public:
    Ghost(int startX, int startY);
    void update(sf::Vector2i pacmanPosition);
    void draw(sf::RenderWindow &window);
    sf::Vector2i getPosition();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i position;
    sf::Clock movementClock;

    void moveRandomly();
    void chasePacman(sf::Vector2i pacmanPosition);
    bool canMoveTo(int x, int y);
};


#endif
