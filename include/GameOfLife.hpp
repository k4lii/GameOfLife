#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <SFML/Graphics.hpp>
#include <vector>

class GameOfLife {
public:
    GameOfLife(int width, int height);
    void Update();
    void SFMLDraw();
    void SFMLEvents();
    void RandGridCells();
    void printGrid() const; // Print grid to console for debugging
    sf::RenderWindow window;
    sf::VertexArray vertices_tab;
private:
    std::vector<std::vector<bool>> game_map;
    sf::Event event;
    inline int SFMLGetVertexIndex(int x, int y, int height);
    int width;
    int height;
    int cell_size;

    void InitGrid();
    int CountNeighbors(int x, int y);
};

#endif
