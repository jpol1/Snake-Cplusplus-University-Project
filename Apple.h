#ifndef SNAKESFML_APPLE_H
#define SNAKESFML_APPLE_H
#include <random>
#include <SFML/Graphics.hpp>

class Apple {
    int AppleX_;
    int AppleY_;
    std::mt19937 gen_;
public:
    Apple();
    void randomizePosition();
    [[nodiscard]] sf::RectangleShape drawApple() const;
    [[nodiscard]] int AppleX() const { return AppleX_; }
    [[nodiscard]] int AppleY() const { return AppleY_; }

};
#endif //SNAKESFML_APPLE_H