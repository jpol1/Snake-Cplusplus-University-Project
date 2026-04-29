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

void Snake::setAlive() {
    if (headX() < 0 || headX() >= COLS || headY() < 0 || headY() >= ROWS) {
        isAlive_ = false;
    }
}

void Snake::increaseSnake(const sf::Vector2i tail) {
    body_.push_back(tail);
}

void Snake::drawEyes(sf::RenderWindow& window) const{
    const sf::Vector2i head = body_.front();
    float left_x;
    float left_y;
    float right_x;
    float right_y;

    if (snakeDirection() == DIRECTION::RIGHT) {
        left_x = 10;
        left_y = 5;
        right_x = 10;
        right_y = 15;

    }
    else if (snakeDirection() == DIRECTION::LEFT) {
        left_x = 5;
        left_y = 5;
        right_x = 5;
        right_y = 15;
    }
    else if (snakeDirection() == DIRECTION::UP) {
        left_x = 5;
        left_y = 6;
        right_x = 15;
        right_y = 6;
    }
    else {
        left_x = 5;
        left_y = 8;
        right_x = 15;
        right_y = 8;
    }



    sf::RectangleShape shape(sf::Vector2f(SIZE_CELL*0.1 , SIZE_CELL*0.1));
    shape.setFillColor(sf::Color::Yellow);

    shape.setPosition(sf::Vector2f(SIZE_CELL * static_cast<float>(head.x) + left_x,
                                    SIZE_CELL * static_cast<float>(head.y) + left_y));
    window.draw(shape);

    shape.setPosition(sf::Vector2f(SIZE_CELL * static_cast<float>(head.x) + right_x,
                                    SIZE_CELL * static_cast<float>(head.y)+ right_y));
    window.draw(shape);

}


void Snake::drawHead(sf::RenderWindow& window) const{
    const sf::Vector2i head = body_.front();
    sf::RectangleShape shape(sf::Vector2f(SIZE_CELL, SIZE_CELL));
    shape.setPosition(sf::Vector2f(SIZE_CELL * static_cast<float>(head.x),
                                    SIZE_CELL * static_cast<float>(head.y)));
    shape.setFillColor(sf::Color(0, 165, 0));
    window.draw(shape);
}


void Snake::drawSnake(sf::RenderWindow& window) const{
    drawHead(window);
    drawEyes(window);
    for(int i = 1; i < body_.size(); i++) {
        sf::RectangleShape shape(sf::Vector2f(SIZE_CELL, SIZE_CELL));
        shape.setPosition(sf::Vector2f(SIZE_CELL * static_cast<float>(body_[i].x),
                                        SIZE_CELL * static_cast<float>(body_[i].y)));
        shape.setFillColor(sf::Color::Green);
        window.draw(shape);
    }
}