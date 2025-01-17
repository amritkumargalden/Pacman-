#ifndef PACMAN_H
#define PACMAN_H

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Pacman {
public:
    Pacman(Maze* maze);  // Changed to pointer instead of reference
    void handleInput();
    void update();
    void draw(sf::RenderWindow &window);
    sf::Vector2i getPosition();
    void reset();  // Added reset function

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i position;
    Maze* maze;  // Changed to pointer instead of reference
};

#endif
