#include "Snake.h"
#include "Direction.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

Snake::Snake():
snakeX_(20.f),
snakeY_(15.f),
snakeDirection_(DIRECTION::RIGHT),
snakeLives_(1){};

void Snake::setSnakeDirection(DIRECTION direction) {
    snakeDirection_ = direction;
}

void Snake::moveSnake() {
    if (snakeDirection_ == DIRECTION::RIGHT) {
        snakeX_++;
    }
    else if (snakeDirection_ == DIRECTION::LEFT) {
        snakeX_--;
    }
    else if (snakeDirection_ == DIRECTION::UP) {
        snakeY_--;
    }
    else if (snakeDirection_ == DIRECTION::DOWN) {
        snakeY_++;
    }
}

sf::RectangleShape Snake::drawSnake() const{
    sf::RectangleShape shape(sf::Vector2f(SIZE_CELL, SIZE_CELL));
    shape.setPosition(sf::Vector2f(SIZE_CELL * snakeX(),SIZE_CELL * snakeY()));
    shape.setFillColor(sf::Color::Green);
    return shape;
}

void Snake::increaseLives() {
    snakeLives_++;
}