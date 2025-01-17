#include "Ghost.h"

Ghost::Ghost(int startX, int startY) : position(startX, startY) {
    // Load the ghost texture
    if (!texture.loadFromFile("assets/ghost.png")) {
        std::cerr << "Error: Could not load ghost texture!" << std::endl;
    }
	
	// Set the texture and initial position
    sprite.setTexture(texture);
    sprite.setPosition(position.x * 40, position.y * 40);
    sprite.setColor(sf::Color::Red); // Default color for the ghost
    
    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Ghost::update(sf::Vector2i pacmanPosition) {
    // Move ghost periodically (e.g., every 0.5 seconds)
    if (movementClock.getElapsedTime().asSeconds() > 0.5f) {
        int behavior = std::rand() % 2; // 0 = random, 1 = chase Pac-Man
        if (behavior == 0) {
            moveRandomly();
        } else {
            chasePacman(pacmanPosition);
        }
        movementClock.restart();
    }
    sprite.setPosition(position.x * 40, position.y * 40);
}

void Ghost::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::Vector2i Ghost::getPosition() {
    return position;
}

void Ghost::moveRandomly() {
    int direction = std::rand() % 4; // Random direction: 0=up, 1=down, 2=left, 3=right
    switch (direction) {
        case 0: if (canMoveTo(position.x, position.y - 1)) position.y--; break;
        case 1: if (canMoveTo(position.x, position.y + 1)) position.y++; break;
        case 2: if (canMoveTo(position.x - 1, position.y)) position.x--; break;
        case 3: if (canMoveTo(position.x + 1, position.y)) position.x++; break;
    }
}

void Ghost::chasePacman(sf::Vector2i pacmanPosition) {
    // Simple chasing logic: move closer to Pac-Man
    if (position.x < pacmanPosition.x && canMoveTo(position.x + 1, position.y)) {
        position.x++;
    } else if (position.x > pacmanPosition.x && canMoveTo(position.x - 1, position.y)) {
        position.x--;
    } else if (position.y < pacmanPosition.y && canMoveTo(position.x, position.y + 1)) {
        position.y++;
    } else if (position.y > pacmanPosition.y && canMoveTo(position.x, position.y - 1)) {
        position.y--;
    }
}

bool Ghost::canMoveTo(int x, int y) {
    // Basic boundary checking
    if (x < 0 || x >= 10 || y < 0 || y >= 10) {
        return false;
    }
    
    // For now, just prevent ghosts from going out of bounds
    // In a full implementation, this should check the maze grid
    return true;
}

