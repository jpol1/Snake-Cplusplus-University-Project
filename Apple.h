#ifndef SNAKESFML_APPLE_H
#define SNAKESFML_APPLE_H
#include <random>
#include <SFML/Graphics.hpp>

class Apple {
    float AppleX_;
    float AppleY_;
    std::mt19937 gen_;
public:
    Apple();
    void randomizePosition();
    [[nodiscard]] sf::RectangleShape drawApple() const;
    [[nodiscard]] float AppleX() const { return AppleX_; }
    [[nodiscard]] float AppleY() const { return AppleY_; }

};
#endif //SNAKESFML_APPLE_H