#include <SFML/Graphics.hpp>
#include "Constants.h"

void drawGrid(sf::RenderWindow& window){
    sf::RectangleShape verticalLine(sf::Vector2f(1, WINDOW_HEIGHT));
    verticalLine.setFillColor(sf::Color(40,40,40));

    sf::RectangleShape horizontalLine(sf::Vector2f(WINDOW_WIDTH, 1));
    horizontalLine.setFillColor(sf::Color(40,40,40));

    for (int x = 0; x <= 800; x += 20) {
        verticalLine.setPosition(sf::Vector2f(static_cast<float>(x),0.f));
        window.draw(verticalLine);
    }

    for (int y = 0; y <= 600; y += 20) {
        horizontalLine.setPosition(sf::Vector2f(0.f, static_cast<float>(y)));
        window.draw(horizontalLine);
    }
}
