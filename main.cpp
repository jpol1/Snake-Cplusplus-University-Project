#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Constants.h"
#include "Apple.h"
#include "Window.h"

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