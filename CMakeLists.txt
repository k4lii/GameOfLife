cmake_minimum_required(VERSION 3.10)

# Activer la politique CMP0074 pour autoriser find_package à utiliser SFML_ROOT
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

# Inclure le dossier include pour les headers internes
include_directories(${PROJECT_SOURCE_DIR}/include)

# Configuration de SFML en fonction de l'OS
if(APPLE)
    # Chemin spécifique pour SFML installé via Homebrew sur macOS
    set(SFML_ROOT "/opt/homebrew/opt/sfml")
    set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake/SFML")
    find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
elseif(UNIX)
    # Configuration Linux (déjà fonctionnelle sur ton autre PC)
    find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
endif()

# Ajouter les fichiers source
add_executable(GameOfLife src/main.cpp src/GameOfLife.cpp)

# Lier les bibliothèques SFML
target_link_libraries(GameOfLife
    sfml-graphics
    sfml-window
    sfml-system
)
