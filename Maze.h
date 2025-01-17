#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>

class Maze {
public:
    Maze() = default;
    bool loadMaze();  // Changed to return bool to match implementation
    void draw(sf::RenderWindow &window);
    int checkCollision(sf::Vector2i position);

    static const int width = 10;
    static const int height = 10;
    
private:
    int maze[height][width];  // Changed from grid to maze to match implementation
    sf::Texture wallTexture, pelletTexture;
    sf::Sprite wallSprite, pelletSprite;
};

#endif
