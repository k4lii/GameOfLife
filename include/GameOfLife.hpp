#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <SFML/Graphics.hpp>
#include <vector>

class GameOfLife {
public:
    GameOfLife(int width, int height);
    // void update();
    void draw();
    void handle_event();
    void RandGridCells();
    void printGrid() const; // Print grid to console for debugging
    sf::RenderWindow window;

private:
    std::vector<std::vector<bool>> game_map;
    sf::Event event;
    int width;
    int height;

    void initGrid();
    int countNeighbors(int x, int y);
};

#endif
