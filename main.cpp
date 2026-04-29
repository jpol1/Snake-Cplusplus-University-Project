#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Constants.h"
#include "Apple.h"
#include "Window.h"

int main() {
    float WINDOW_REFRESHING = 0.2f;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake");

    Snake snake;
    snake.drawSnake(window);

    Apple apple;
    apple.randomizePosition();
    apple.drawApple(window);

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

        if (clock.getElapsedTime().asSeconds() >= WINDOW_REFRESHING) {
            sf::Vector2i tmp_tail = snake.tail();
            snake.moveSnake();

            if (snake.headX() == apple.AppleX() && snake.headY() == apple.AppleY()) {
                apple.randomizePosition();
                snake.increaseSnake(tmp_tail);
                WINDOW_REFRESHING *= 0.95 ;
            }

            snake.setAlive();
            if (!snake.isAlive()) {
                break;
            }
            clock.restart();
        }

        window.clear();

        drawGrid(window);

        apple.drawApple(window);
        snake.drawSnake(window);

        window.display();
    }

    return 0;
}