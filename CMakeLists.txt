cmake_minimum_required(VERSION 3.10)

project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

# Ajouter le dossier include pour les headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Ajouter les fichiers source
add_executable(GameOfLife src/main.cpp src/GameOfLife.cpp)

# Lier les bibliothèques SFML
target_link_libraries(GameOfLife
    sfml-graphics
    sfml-window
    sfml-system
)
