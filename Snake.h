//
// Created by Jakub Połeć on 28/04/2026.
//
#ifndef SNAKESFML_SNAKE_H
#define SNAKESFML_SNAKE_H

#include "Direction.h"

class Snake {
    float snakeX_;
    float snakeY_;
    DIRECTION snakeDirection_;
public:
    Snake();
    [[nodiscard]] float snakeX() const {return snakeX_;}
    [[nodiscard]] float snakeY() const {return snakeY_;}
    [[nodiscard]] DIRECTION snakeDirection() const {return snakeDirection_;}

    void moveSnake();
    void setSnakeDirection(DIRECTION direction);
};

#endif //SNAKESFML_SNAKE_H