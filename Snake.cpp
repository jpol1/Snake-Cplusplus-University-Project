#include "Snake.h"
#include "Direction.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

Snake::Snake():
snakeDirection_(DIRECTION::RIGHT),
isAlive_(true),
body_({sf::Vector2i(20,15), sf::Vector2i(19,15)}){};

void Snake::setSnakeDirection(DIRECTION direction) {
    snakeDirection_ = direction;
}

void Snake::moveSnake() {
    for (int i = static_cast<int>(body_.size()) - 1; i>=1; i--) {
        body_[i] = body_[i-1];
    }
    if (snakeDirection_ == DIRECTION::RIGHT) {
        body_.front().x++;
    }
    else if (snakeDirection_ == DIRECTION::LEFT) {
        body_.front().x--;
    }
    else if (snakeDirection_ == DIRECTION::UP) {
        body_.front().y--;
    }
    else if (snakeDirection_ == DIRECTION::DOWN) {
        body_.front().y++;
    }
}

void Snake::drawSnake(sf::RenderWindow& window) const{
    for(auto const body: body_) {
        sf::RectangleShape shape(sf::Vector2f(SIZE_CELL, SIZE_CELL));
        shape.setPosition(sf::Vector2f(SIZE_CELL * static_cast<float>(body.x),
                                        SIZE_CELL * static_cast<float>(body.y)));
        shape.setFillColor(sf::Color::Green);
        window.draw(shape);
    }
}

void Snake::setAlive() {
    if (headX() < 0 || headX() >= COLS || headY() < 0 || headY() >= ROWS) {
        isAlive_ = false;
    }
}

void Snake::increaseSnake(const sf::Vector2i tail) {
    body_.push_back(tail);
}
