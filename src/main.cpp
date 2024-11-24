#include "GameOfLife.hpp"
// #include "GameOfLife.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    GameOfLife game(1000, 1000, 2); // Grid size: 10x10, cell size: 40 pixels
    game.RandGridCells();
    // game.loadPatternFromFile("./test.rle");

    while (game.window.isOpen()) {
        game.SFMLEvents();   // Handle events
        game.ApplyRules();   // Update game logic
        game.UpdateMatrix(); // Update vertices for rendering
        game.SFMLDraw();     // Draw the updated grid

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Pause for visualization
    }

    return 0;
}
