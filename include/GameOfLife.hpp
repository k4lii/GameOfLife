#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <SFML/Graphics.hpp>
#include <vector>

class GameOfLife {
public:
    sf::RenderWindow window;
    GameOfLife(int width, int height, int cell_size);

    void SFMLDraw();
    void SFMLEvents();
    void ApplyRules();
    void RandGridCells();
    void printGrid() const;
    void UpdateMatrix();
    void loadPatternFromFile(const std::string& filename);

private:
    std::vector<std::vector<int>> game_map;
    sf::Event event;
    sf::VertexArray vertices_tab;
    int width;
    int height;
    int cell_size;
    void initializeGrid(int width, int height);


    void inline SFMLUpdate(int index, int x, int y);
    int inline CountAroundCells(int x, int y);
    void InitGrid();
};

#endif
