#include "GameOfLife.hpp"

GameOfLife::GameOfLife(int width, int height) : width(width), height(height) {
    initGrid();
}

void GameOfLife::initGrid() {
    grid.resize(height, std::vector<bool>(width, false));
    nextGrid = grid;
}

int GameOfLife::countNeighbors(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                count += grid[ny][nx];
            }
        }
    }
    return count;
}

void GameOfLife::update() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int neighbors = countNeighbors(x, y);
            nextGrid[y][x] = (grid[y][x] && (neighbors == 2 || neighbors == 3)) ||
                             (!grid[y][x] && neighbors == 3);
        }
    }
    grid = nextGrid;
}

void GameOfLife::draw(sf::RenderWindow &window) {
    sf::RectangleShape cell(sf::Vector2f(10, 10));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x]) {
                cell.setPosition(x * 10, y * 10);
                window.draw(cell);
            }
        }
    }
}
