#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <SFML/Graphics.hpp>
#include <vector>

class GameOfLife {
public:
    GameOfLife(int width, int height);
    void update();
    void draw(sf::RenderWindow &window);

private:
    int width;
    int height;
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> nextGrid;

    void initGrid();
    int countNeighbors(int x, int y);
};

#endif
