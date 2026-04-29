#include <SFML/Graphics.hpp>
#include "../include/Constants.h"
#include "../include/Direction.h"
#include "../include/Snake.h"
#include "../include/Apple.h"
#include <iostream>

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

void drawCounter(sf::RenderWindow& window, int snakeSize) {
    sf::Font font;
    if (!font.openFromFile("../assets/fonts/Comic Sans MS.ttf")) {
        std::cout << "Failed to load font\n";
    };

    sf::Text text(font);
    text.setString(std::to_string(snakeSize-2));
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition({760 , 20});
    window.draw(text);
}

void drawGameOver(sf::RenderWindow& window, int snakeSize) {
    sf::Font font;

    if (!font.openFromFile("../assets/fonts/Comic Sans MS.ttf")) {
        std::cout << "Failed to load font\n";
    };

    sf::Text title(font);
    title.setString("GAME OVER");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color(120,0,0));

    auto titleBounds = title.getLocalBounds();
    title.setPosition({
        WINDOW_WIDTH / 2.f - titleBounds.size.x / 2.f,
        WINDOW_HEIGHT / 2.f - titleBounds.size.y / 2.f
    });

    sf::Text score(font);
    score.setString("Your score: " + std::to_string(snakeSize-2));
    score.setCharacterSize(50);
    score.setFillColor(sf::Color::White);
    score.setPosition({
        title.getPosition().x,
        title.getPosition().y - 90
    });


    sf::Text restart(font);
    restart.setString("Click R to Restart");
    restart.setCharacterSize(30);
    restart.setFillColor(sf::Color::White);
    restart.setPosition({
        title.getPosition().x,
        title.getPosition().y - 160
    });

    window.draw(title);
    window.draw(score);
    window.draw(restart);
}

void runGame(sf::RenderWindow& window, sf::Clock& clock, Snake& snake, Apple& apple){
    bool gameOver = false;
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
                else if (key->code == sf::Keyboard::Key::R && gameOver == true) {
                    snake = Snake();
                    apple.randomizePosition();
                    gameOver = false;
                }
            }
        }

        if (!gameOver && clock.getElapsedTime().asSeconds() >= snake.snakeSpeed()) {
            sf::Vector2i tmp_tail = snake.tail();
            snake.moveSnake();

            if (snake.headX() == apple.AppleX() && snake.headY() == apple.AppleY()) {
                apple.randomizePosition();
                snake.increaseSnake(tmp_tail);
                snake.increaseSpeed();
            }

            snake.setAlive();
            if (!snake.isAlive()) {
                gameOver = true;
            }
            clock.restart();
        }

        window.clear();

        drawGrid(window);
        drawCounter(window, snake.bodySize());
        apple.drawApple(window);
        snake.drawSnake(window);

        if (gameOver) {
            window.clear();
            drawGameOver(window, snake.bodySize());
        }

        window.display();
    }
}