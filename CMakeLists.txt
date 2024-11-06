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

# Récupérer tous les fichiers .cpp dans le dossier src
file(GLOB SOURCES "src/*.cpp")

# Ajouter les fichiers source à l'exécutable
add_executable(GameOfLife ${SOURCES})

# Lier les bibliothèques SFML
target_link_libraries(GameOfLife
    sfml-graphics
    sfml-window
    sfml-system
)

# Configuration de CPack pour générer des installateurs multiplateformes
include(CPack)

# Choisir le type d'installateur en fonction de la plateforme
if(WIN32)
    set(CPACK_GENERATOR "WIX") # ou NSIS pour un EXE
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB;RPM") # Génère des paquets .deb et .rpm
endif()

# Informations du package
set(CPACK_PACKAGE_NAME "GameOfLife")
set(CPACK_PACKAGE_VERSION "0.1")
set(CPACK_PACKAGE_CONTACT "lorris@fortea.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "lorris@fortea.com")
