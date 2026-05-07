#ifndef SNAKESFML_APPLE_H
#define SNAKESFML_APPLE_H
#include <random>
#include <SFML/Graphics.hpp>
#include "Snake.h"

class Apple {
    int AppleX_;
    int AppleY_;
    std::mt19937 gen_;
public:
    Apple();
    void randomizePosition();
    [[nodiscard]] int AppleX() const { return AppleX_; }
    [[nodiscard]] int AppleY() const { return AppleY_; }
    void drawApple(sf::RenderWindow& window) const;
    bool positionInSnake(const Snake& snake) const;
};
#endif //SNAKESFML_APPLE_H