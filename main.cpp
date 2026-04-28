#include <SFML/Graphics.hpp>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr float SIZE_CELL = 20.f;

constexpr int COLS = WINDOW_WIDTH / SIZE_CELL;
constexpr int ROWS = WINDOW_HEIGHT / SIZE_CELL;

void drawGrid(sf::RenderWindow& window) {
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

enum class DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int main() {
    float snakeX = 20.f;
    float snakeY = 15.f;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake");

    sf::RectangleShape shape(sf::Vector2f(SIZE_CELL, SIZE_CELL));
    shape.setPosition(sf::Vector2f(SIZE_CELL * snakeX,SIZE_CELL * snakeY));
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();

        drawGrid(window);

        window.draw(shape);
        window.display();
    }

    return 0;
}