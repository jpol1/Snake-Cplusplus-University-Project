#include <SFML/Graphics.hpp>
#include "../include/Snake.h"
#include "../include/Constants.h"
#include "../include/Apple.h"
#include "../include/Window.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake");

    Snake snake;
    snake.drawSnake(window);

    Apple apple;
    apple.randomizePosition();
    apple.drawApple(window);

    sf::Clock clock;

    runGame(window, clock, snake, apple);

    return 0;
}