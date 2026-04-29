#ifndef SNAKESFML_SNAKE_H
#define SNAKESFML_SNAKE_H

#include "Direction.h"
#include <SFML/Graphics.hpp>

class Snake {
    DIRECTION snakeDirection_;
    bool isAlive_;
    float snakeSpeed_;
    std::vector<sf::Vector2i> body_;
public:
    Snake();
    [[nodiscard]] int headX() const {return body_[0].x;}
    [[nodiscard]] int headY() const {return body_[0].y;}
    [[nodiscard]] sf::Vector2i tail() const {return body_.back();}
    [[nodiscard]] DIRECTION snakeDirection() const {return snakeDirection_;}
    [[nodiscard]] bool isAlive() const {return isAlive_;}
    [[nodiscard]] int bodySize() const {return static_cast<int>(body_.size());}
    [[nodiscard]] float snakeSpeed() const{return snakeSpeed_;};

    void moveSnake();

    void drawEyes(sf::RenderWindow& window) const;
    void drawHead(sf::RenderWindow& window) const;
    void drawSnake(sf::RenderWindow& window) const;


    void setSnakeDirection(DIRECTION direction);
    void setAlive();

    void increaseSnake(sf::Vector2i tail);
    void increaseSpeed();
};

#endif //SNAKESFML_SNAKE_H