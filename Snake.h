#ifndef SNAKESFML_SNAKE_H
#define SNAKESFML_SNAKE_H

#include "Direction.h"
#include <SFML/Graphics.hpp>

class Snake {
    float snakeX_;
    float snakeY_;
    DIRECTION snakeDirection_;
    int snakeLives_;
public:
    Snake();
    [[nodiscard]] float snakeX() const {return snakeX_;}
    [[nodiscard]] float snakeY() const {return snakeY_;}
    [[nodiscard]] DIRECTION snakeDirection() const {return snakeDirection_;}

    void moveSnake();
    [[nodiscard]] sf::RectangleShape drawSnake() const;

    void setSnakeDirection(DIRECTION direction);
    void increaseLives();
};

#endif //SNAKESFML_SNAKE_H