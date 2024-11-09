#include "GameOfLife.hpp"
#include <SFML/Graphics.hpp>


int main()
{
    GameOfLife GameOfLife(10, 10, 20);
    GameOfLife.RandGridCells();
    GameOfLife.printGrid();
    //essayer d'aficher chaque cellule
    //coder la logique du jeu de la vie

    while (GameOfLife.window.isOpen()) {
        GameOfLife.SFMFEvent();
        GameOfLife.Update();
        GameOfLife.SFMLDraw();
    }
    return 0;
}