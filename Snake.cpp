//
// Created by Jakub Połeć on 28/04/2026.
//

#include "Snake.h"
#include "Direction.h"

Snake::Snake():
snakeX_(20.f),
snakeY_(15.f),
snakeDirection_(DIRECTION::RIGHT){};

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