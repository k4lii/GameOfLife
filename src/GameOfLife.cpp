#include "GameOfLife.hpp"
#include <iostream>

GameOfLife::GameOfLife(int width, int height, int cell_size)  : cell_size(cell_size), width(width), height(height), window(sf::VideoMode(width, height), "SFML works!") {
    this->window.setVerticalSyncEnabled(false);
    this->window(sf::VideoMode(width * cell_size, height * cell_size), "Game of Life - SFML");
    this->vertices_tab(sf::Quads, width * height * 4); // Create a vertex array for the grid
    InitGrid();
}

void GameOfLife::InitGrid() {
    this->game_map = std::vector<std::vector<bool>>(this->width, std::vector<bool>(this->height, false));
}

void GameOfLife::SFMLEvents() {
    while (this->window.pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window.close();
    }
}

void GameOfLife::Update(){
    int index = 0;  // Compteur pour avancer dans vertices_tab
    for (int y = 0; y < this->width; ++y) {
        for (int x = 0; x < this->height; ++x) {
            // Positions des sommets
            sf::Vector2f topLeft(x * this->this->cellSize, y * this->cellSize);
            sf::Vector2f topRight((x + 1) * this->cellSize, y * this->cellSize);
            sf::Vector2f bottomRight((x + 1) * this->cellSize, (y + 1) * this->cellSize);
            sf::Vector2f bottomLeft(x * this->cellSize, (y + 1) * this->cellSize);

            // Couleur pour cette cellule
            sf::Color cellColor = grid[y][x] == 1 ? sf::Color::Green : sf::Color::Black;

            // Affecter directement les sommets
            this->vertices_tab[index++] = sf::Vertex(topLeft, cellColor);
            this->vertices_tab[index++] = sf::Vertex(topRight, cellColor);
            this->vertices_tab[index++] = sf::Vertex(bottomRight, cellColor);
            this->vertices_tab[index++] = sf::Vertex(bottomLeft, cellColor);
        }
    }
}

void GameOfLife::SFMLDraw() {
    this->window.clear();
    this->window.draw(this->gridVertices); //afficher l'array de vertex
    this->window.display();
}


// int GameOfLife::countNeighbors(int x, int y) {

// }



// ╔══════════════════════════════════════════════════════════════════════════╗
// ║                                 TOOLS                                    ║
// ╚══════════════════════════════════════════════════════════════════════════╝


// inline int SFMLGetVertexIndex(int x, int y, int height) { //utlisation de inline pour compiler la fonction dans la fonction LOL
//     return (y * height + x) * 4;
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
