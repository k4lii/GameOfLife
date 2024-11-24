#include "GameOfLife.hpp"
#include <iostream>
#include <fstream>    // For std::ifstream
#include <sstream>    // For std::istringstream
#include <iostream>   // For std::cerr and std::cout (if not already included)


// Constructor
GameOfLife::GameOfLife(int width, int height, int cell_size)
    : cell_size(cell_size), width(width), height(height),
      window(sf::VideoMode(width * cell_size, height * cell_size), "Game of Life - SFML"),
      vertices_tab(sf::Quads, width * height * 4) {
    this->window.setVerticalSyncEnabled(true); // Enable VSync for smooth rendering
    InitGrid();
}

// Initialize the grid
void GameOfLife::InitGrid() {
    this->game_map = std::vector<std::vector<int>>(this->height, std::vector<int>(this->width, 0));
}

// Handle SFML events
void GameOfLife::SFMLEvents() {
    while (this->window.pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window.close();
    }
}

// Count neighbors for a cell
int inline GameOfLife::CountAroundCells(int x, int y) {
    int count = 0;
    const int directions[8][2] = {
        {-1, -1}, {-1,  0}, {-1,  1},
        { 0, -1},          { 0,  1},
        { 1, -1}, { 1,  0}, { 1,  1}
    };

    for (int i = 0; i < 8; ++i) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
            count += game_map[newY][newX];
        }
    }

    return count;
}

// Update vertex data for a specific cell
void inline GameOfLife::SFMLUpdate(int index, int x, int y) {
    sf::Vector2f topLeft(x * this->cell_size, y * this->cell_size);
    sf::Vector2f topRight((x + 1) * this->cell_size, y * this->cell_size);
    sf::Vector2f bottomRight((x + 1) * this->cell_size, (y + 1) * this->cell_size);
    sf::Vector2f bottomLeft(x * this->cell_size, (y + 1) * this->cell_size);

    sf::Color cellColor = (this->game_map[y][x] == 1) ? sf::Color::Green : sf::Color::Black;

    this->vertices_tab[index]     = sf::Vertex(topLeft, cellColor);
    this->vertices_tab[index + 1] = sf::Vertex(topRight, cellColor);
    this->vertices_tab[index + 2] = sf::Vertex(bottomRight, cellColor);
    this->vertices_tab[index + 3] = sf::Vertex(bottomLeft, cellColor);
}

// Apply game logic
void GameOfLife::ApplyRules() {
    std::vector<std::vector<int>> new_game_map = game_map;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int neighbors = CountAroundCells(x, y);

            if (game_map[y][x] == 1) {
                new_game_map[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                new_game_map[y][x] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    this->game_map = new_game_map;
}

// Update vertex array for rendering
void GameOfLife::UpdateMatrix() {
    int index = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            SFMLUpdate(index, x, y);
            index += 4;
        }
    }
}

// Draw the grid
void GameOfLife::SFMLDraw() {
    this->window.clear();
    this->window.draw(this->vertices_tab);
    this->window.display();
}

// Print the grid to the console
void GameOfLife::printGrid() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << (game_map[y][x] ? "1" : "0") << " ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------\n";
}

// Generate a random grid
void GameOfLife::RandGridCells() {
    std::srand(std::time(nullptr));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            game_map[y][x] = (std::rand() % 2); // Random 0 or 1
        }
    }
}




void GameOfLife::initializeGrid(int width, int height) {
    this->width = width;
    this->height = height;
    this->game_map.resize(height, std::vector<int>(width, 0));
    window.create(sf::VideoMode(width * cell_size, height * cell_size), "Game of Life");
}

void GameOfLife::loadPatternFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::string line;
    int x = 0, y = 0;
    while (std::getline(file, line)) {
        if (line[0] == '#') continue; // Skip comments
        if (line.substr(0, 2) == "x ") {
            std::istringstream iss(line);
            char ch;
            iss >> ch >> ch >> x >> ch >> ch >> y;
            initializeGrid(x, y);
            continue;
        }
        // Parse RLE data here and populate the grid
    }
    file.close();
}
