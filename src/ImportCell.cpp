// #include "GameOfLife.hpp"

// void GameOfLife::initializeGrid(int width, int height) {
//     this->width = width;
//     this->height = height;
//     this->
//     this->game_map.resize(height, std::vector<int>(width, 0));
//     window.create(sf::VideoMode(width * cell_size, height * cell_size), "Game of Life");
// }

// void GameOfLife::loadPatternFromFile(const std::string& filename) {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error opening file\n";
//         return;
//     }

//     std::string line;
//     int x = 0, y = 0;
//     while (std::getline(file, line)) {
//         if (line[0] == '#') continue; // Skip comments
//         if (line.substr(0, 2) == "x ") {
//             std::istringstream iss(line);
//             char ch;
//             iss >> ch >> ch >> x >> ch >> ch >> y;
//             initializeGrid(x, y);
//             continue;
//         }
//         // Parse RLE data here and populate the grid
//     }
//     file.close();
// }
