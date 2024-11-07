#include "GameOfLife.hpp"
#include <SFML/Graphics.hpp>


int main()
{

    GameOfLife GameOfLife(10,10);
    GameOfLife.RandGridCells();
    GameOfLife.printGrid();
    // while (GameOfLife.window.isOpen()) {
    //     GameOfLife.handle_event();
    //     GameOfLife.draw();
    // }
    return 0;
}