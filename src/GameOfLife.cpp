#include "GameOfLife.hpp"
#include <iostream>

GameOfLife::GameOfLife(int width, int height)  : width(width), height(height), window(sf::VideoMode(width, height), "SFML works!") {
    this->window.setVerticalSyncEnabled(false);
    initGrid();
}

void GameOfLife::initGrid() {
    this->game_map = std::vector<std::vector<bool>>(this->width, std::vector<bool>(this->height, false));
}

void GameOfLife::handle_event() {
    while (this->window.pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window.close();
    }
}

void GameOfLife::draw() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    this->window.clear();
    this->window.draw(shape);
    this->window.display();
}


// int GameOfLife::countNeighbors(int x, int y) {

// }








// ╔══════════════════════════════════════════════════════════════════════════╗
// ║                                TESTING                                   ║
// ╚══════════════════════════════════════════════════════════════════════════╝

void GameOfLife::printGrid() const {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            std::cout << (game_map[x][y] ? "1 " : "0 ");  // Print `1` for true, `0` for false
        }
        std::cout << "\n";
    }
}

void GameOfLife::RandGridCells() {
    std::srand(std::time(nullptr));  // Initialisation de la graine
    for (int x = 0; x < this->width; ++x) {
        for(int y = 0; y < this->height; ++y){
              game_map[x][y] = (std::rand() % 2 == 0);  // 50% chance vivante ou morte
        }
    }
}
