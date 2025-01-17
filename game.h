#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Maze.h"
#include "Pacman.h"
#include "Ghost.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;
    sf::SoundBuffer chompBuffer, powerUpBuffer;
    sf::Sound chompSound, powerUpSound;

    Maze maze;
    Pacman pacman;  // Will be initialized with &maze in constructor
    std::vector<Ghost> ghosts;
    int score;

    void processEvents();
    void update();
    void render();
    void resetGame();
};

#endif
