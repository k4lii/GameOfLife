#include "GameOfLife.hpp"
#include <iostream>
#include <fstream>    // For file I/O
#include <sstream>    // For string streams
#include <filesystem> // For directory scanning
namespace fs = std::filesystem; // Alias for convenience
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For seeding rand()

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

void GameOfLife::RandGridCells() {
    // Seed the random number generator with the current time
    std::srand(std::time(0));
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Assign a random value: 1 (alive) or 0 (dead) with equal probability
            game_map[y][x] = std::rand() % 2;
        }
    }
}
// Initialize grid dimensions
void GameOfLife::initializeGrid(int width, int height) {
    if (width > this->width || height > this->height) {
        std::cerr << "Pattern exceeds current grid size.\n";
        return;
    }
}

// Load RLE pattern from file
void GameOfLife::loadPatternFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    std::string line;
    int x = 0, y = 0;
    int startX = 5, startY = 5; // Offset to place pattern in grid
    int currentX = startX, currentY = startY;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        if (line.substr(0, 2) == "x ") {
            std::istringstream iss(line);
            std::string temp;
            iss >> temp >> x >> temp >> temp >> y;
            continue;
        }

        int count = 0;
        for (char ch : line) {
            if (isdigit(ch)) {
                count = count * 10 + (ch - '0');
            } else if (ch == 'b' || ch == 'o') {
                count = (count == 0) ? 1 : count;
                for (int i = 0; i < count; ++i) {
                    if (currentX >= this->width) {
                        currentX = startX;
                        ++currentY;
                    }
                    if (currentY >= this->height) break;
                    game_map[currentY][currentX] = (ch == 'o') ? 1 : 0;
                    ++currentX;
                }
                count = 0;
            } else if (ch == '$') {
                currentX = startX;
                ++currentY;
            } else if (ch == '!') {
                break;
            }
        }
    }

    file.close();
    std::cout << "Loaded pattern from: " << filename << "\n";
}

// Load all RLE files from a folder
void GameOfLife::loadPatternsFromFolder(const std::string& folderPath) {
    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.path().extension() == ".rle") {
                loadPatternFromFile(entry.path().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing folder: " << e.what() << "\n";
    }
}
