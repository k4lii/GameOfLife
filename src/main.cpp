#include <SFML/Graphics.hpp>
#include "GameOfLife.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game of Life");

    GameOfLife game(800, 600);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        game.update();
        game.draw(window);
        window.display();
    }

    return 0;
}
