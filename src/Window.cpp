#include <SFML/Graphics.hpp>
#include "../include/Constants.h"
#include "../include/Direction.h"
#include "../include/Snake.h"
#include "../include/Apple.h"

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

void runGame(sf::RenderWindow& window, sf::Clock& clock, Snake& snake, Apple& apple, float snake_speed){
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

        if (clock.getElapsedTime().asSeconds() >= snake_speed) {
            sf::Vector2i tmp_tail = snake.tail();
            snake.moveSnake();

            if (snake.headX() == apple.AppleX() && snake.headY() == apple.AppleY()) {
                apple.randomizePosition();
                snake.increaseSnake(tmp_tail);
                snake_speed *= 0.99 ;
            }

            snake.setAlive();
            if (!snake.isAlive()) {
                break;
            }
            clock.restart();
        }

        window.clear();

        drawGrid(window);

        snake.drawCounter(window);
        apple.drawApple(window);
        snake.drawSnake(window);

        window.display();
    }
}