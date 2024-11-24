#include "GameOfLife.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    GameOfLife game(100, 100, 20); // Adjust grid size as needed
    //game.RandGridCells();

    // Load all RLE files from the "cells" folder
    game.loadPatternsFromFolder("./cells");

    while (game.window.isOpen()) {
        game.SFMLEvents();   // Handle events
        game.ApplyRules();   // Update game logic
        game.UpdateMatrix(); // Update vertices for rendering
        game.SFMLDraw();     // Draw the updated grid

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Pause for visualization
    }

    return 0;
}
