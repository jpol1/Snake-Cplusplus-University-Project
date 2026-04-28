#include <SFML/Graphics.hpp>
#include "Snake.h"

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

int main() {
    Snake snake;


    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake");

    sf::RectangleShape shape(sf::Vector2f(SIZE_CELL, SIZE_CELL));
    shape.setPosition(sf::Vector2f(SIZE_CELL * snake.snakeX(),SIZE_CELL * snake.snakeY()));
    shape.setFillColor(sf::Color::Green);


    sf::Clock clock;
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>();

                if (key->code == sf::Keyboard::Key::Left && snake.snakeDirection() != DIRECTION::RIGHT) {
                    snake.setSnakeDirection(DIRECTION::LEFT);
                }
                else if (key->code == sf::Keyboard::Key::Right && snake.snakeDirection() != DIRECTION::LEFT) {
                    snake.setSnakeDirection(DIRECTION::RIGHT);
                }
                else if (key->code == sf::Keyboard::Key::Up && snake.snakeDirection() != DIRECTION::DOWN) {
                    snake.setSnakeDirection(DIRECTION::UP);
                }
                else if (key->code == sf::Keyboard::Key::Down && snake.snakeDirection() != DIRECTION::UP) {
                    snake.setSnakeDirection(DIRECTION::DOWN);
                }
            }
        }

        if (clock.getElapsedTime().asSeconds() >= 0.2f) {
            snake.moveSnake();
            shape.setPosition(sf::Vector2f(SIZE_CELL * snake.snakeX(),SIZE_CELL * snake.snakeY()));
            clock.restart();
        }

        window.clear();

        drawGrid(window);

        window.draw(shape);
        window.display();
    }

    return 0;
}