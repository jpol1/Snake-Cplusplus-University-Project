#include "Apple.h"
#include "Constants.h"
#include <random>
#include <SFML/Graphics.hpp>

Apple::Apple():
    AppleX_(0.f),
    AppleY_(0.f),
    gen_(std::random_device{}()){}

void Apple::randomizePosition() {
    std::uniform_int_distribution<> xDist(0, COLS-1);
    std::uniform_int_distribution<> yDist(0, ROWS-1);

    AppleX_ = xDist(gen_);
    AppleY_ = yDist(gen_);
}

sf::RectangleShape Apple::drawApple() const{
    sf::RectangleShape shape(sf::Vector2f(SIZE_CELL, SIZE_CELL));
    shape.setPosition(sf::Vector2f(SIZE_CELL * AppleX() ,SIZE_CELL * AppleY()));
    shape.setFillColor(sf::Color::Red);
    return shape;
}
