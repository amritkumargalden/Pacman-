#include "Pacman.h"

Pacman::Pacman(Maze* maze) : maze(maze), position(1, 1) {
    if (!texture.loadFromFile("assets/pacman.png")) {
        // Handle error
    }
    sprite.setTexture(texture);
    sprite.setPosition(position.x * 40, position.y * 40);
}

void Pacman::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) position.y--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) position.y++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) position.x--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) position.x++;
}

void Pacman::update() {
    sprite.setPosition(position.x * 40, position.y * 40);
}

void Pacman::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::Vector2i Pacman::getPosition() {
    return position;
}

void Pacman::reset() {
    position = sf::Vector2i(1, 1);
    sprite.setPosition(position.x * 40, position.y * 40);
}
