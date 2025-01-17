#include "Game.h"
#include <iostream>
#include <string>

Game::Game()
    : window(sf::VideoMode(800, 600), "Pac-Man"),
      score(0),
      maze(),
      pacman(&maze) 
{
    // Initialize ghosts vector
    ghosts.push_back(Ghost(1, 1));
    ghosts.push_back(Ghost(8, 1));
    ghosts.push_back(Ghost(1, 8));
    ghosts.push_back(Ghost(8, 8));

    window.setFramerateLimit(60);

    // Load maze
    if (!maze.loadMaze()) {
        std::cerr << "Error: Could not load maze! Check 'assets/maze.txt' for correctness." << std::endl;
        exit(1);
    } else {
        std::cout << "Maze loaded successfully." << std::endl;
    }

    // Load font
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Error: Could not load font! Ensure 'arial.ttf' exists in the 'assets' folder." << std::endl;
        exit(1);
    }

    // Configure score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(10, 10);
    scoreText.setFillColor(sf::Color::White);

    // Load sound effects
    if (!chompBuffer.loadFromFile("assets/sound_effects/chomp.wav")) {
        std::cerr << "Error: Could not load chomp sound! Ensure the file exists." << std::endl;
    } else {
        chompSound.setBuffer(chompBuffer);
    }

    if (!powerUpBuffer.loadFromFile("assets/sound_effects/powerup.wav")) {
        std::cerr << "Error: Could not load power-up sound! Ensure the file exists." << std::endl;
    } else {
        powerUpSound.setBuffer(powerUpBuffer);
    }
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            std::cout << "Window closed." << std::endl;
            window.close();
        }
    }
    pacman.handleInput();
}

void Game::update() {
    pacman.update();

    // Update ghosts
    for (std::vector<Ghost>::iterator it = ghosts.begin(); it != ghosts.end(); ++it) {
        it->update(pacman.getPosition());

        // Debugging: Ghost positions
        std::cout << "Ghost at (" << it->getPosition().x << ", " << it->getPosition().y << ")" << std::endl;

        // Check for collision with Pac-Man
        if (pacman.getPosition() == it->getPosition()) {
            std::cerr << "Collision detected! Resetting game..." << std::endl;
            resetGame();
            return;
        }
    }

    // Check for Pac-Man eating a pellet
    int collisionResult = maze.checkCollision(pacman.getPosition());
    if (collisionResult == 2) { // Pellet eaten
        score++;
        chompSound.play();
        std::cout << "Pellet eaten. Score: " << score << std::endl;
    } else if (collisionResult == 3) { // Power-up eaten
        powerUpSound.play();
        std::cout << "Power-up eaten!" << std::endl;

        // Add "scared" behavior for ghosts
        for (std::vector<Ghost>::iterator it = ghosts.begin(); it != ghosts.end(); ++it) {
            it->setScared(true);
        }
    }

    // Update score display
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::render() {
    window.clear();

    // Draw all game elements
    maze.draw(window);
    pacman.draw(window);
    
    // Draw ghosts with traditional for loop
    for (std::vector<Ghost>::iterator it = ghosts.begin(); it != ghosts.end(); ++it) {
        it->draw(window);
    }
    
    window.draw(scoreText);
    window.display();
}

void Game::resetGame() {
    std::cerr << "Resetting game..." << std::endl;
    pacman.reset();  // Use the new reset function instead of reassignment
    maze.loadMaze();
    score = 0;

    // Reset ghost positions
    ghosts.clear();
    ghosts.push_back(Ghost(1, 1));
    ghosts.push_back(Ghost(8, 1));
    ghosts.push_back(Ghost(1, 8));
    ghosts.push_back(Ghost(8, 8));
}
