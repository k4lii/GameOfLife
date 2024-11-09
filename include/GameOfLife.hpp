#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <SFML/Graphics.hpp>
#include <vector>

class GameOfLife {
public:
    GameOfLife(int width, int height, int cell_size);
    void Update();
    void SFMLDraw();
    void SFMLEvents();
    void RandGridCells();
    void printGrid() const; // Print grid to console for debugging
    sf::RenderWindow window;
private:
    std::vector<std::vector<bool>> game_map;
    sf::Event event;
    inline int SFMLGetVertexIndex(int x, int y, int height);
    int width;
    int height;
    int cell_size;
    sf::VertexArray vertices_tab;

    void InitGrid();
    int CountNeighbors(int x, int y);
};

#endif
