#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Constants.h"
#include "Apple.h"

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
    sf::RectangleShape snake_shape = snake.drawSnake();

    Apple apple;
    apple.randomizePosition();
    sf::RectangleShape apple_shape = apple.drawApple();

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake");


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
            snake_shape.setPosition(sf::Vector2f(SIZE_CELL * snake.snakeX(),SIZE_CELL * snake.snakeY()));
            if (snake_shape.getPosition() == apple_shape.getPosition()) {
                snake.increaseLives();
                while (snake_shape.getPosition() != apple_shape.getPosition()) {
                    apple.randomizePosition();
                }
                apple_shape.setPosition(sf::Vector2f(SIZE_CELL * apple.AppleX(),SIZE_CELL * apple.AppleY()));

            }

            clock.restart();
        }

        window.clear();

        drawGrid(window);

        window.draw(apple_shape);
        window.draw(snake_shape);

        window.display();
    }

    return 0;
}