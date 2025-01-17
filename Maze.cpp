#include "Maze.h"
#include <fstream>
#include <iostream>

bool Maze::loadMaze() {
    std::ifstream file("assets/maze.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open maze file!" << std::endl;
        return false;
    }

    // Debug: File opened successfully
    std::cout << "Maze file loaded successfully!" << std::endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (!(file >> maze[y][x])) {
                std::cerr << "Error: Invalid data at position (" << x << ", " << y << ")" << std::endl;
                return false;
            }
        }
    }

    file.close();
    return true;
}

void Maze::draw(sf::RenderWindow &window) {
    sf::RectangleShape tile(sf::Vector2f(40.f, 40.f));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (maze[y][x] == 1) { // Wall
                tile.setFillColor(sf::Color::Blue);
            } else if (maze[y][x] == 2) { // Pellet
                tile.setFillColor(sf::Color::White);
            } else if (maze[y][x] == 3) { // Power-up
                tile.setFillColor(sf::Color::Yellow);
            } else { // Empty space
                continue;
            }
            tile.setPosition(x * 40, y * 40);
            window.draw(tile);
        }
    }
}

