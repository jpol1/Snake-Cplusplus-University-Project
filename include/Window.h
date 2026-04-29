#ifndef SNAKESFML_WINDOW_H
#define SNAKESFML_WINDOW_H
#include <SFML/Graphics.hpp>

void drawGrid(sf::RenderWindow& window);
void runGame(sf::RenderWindow& window, sf::Clock& clock, Snake& snake, Apple& apple);
void drawCounter(sf::RenderWindow& window);

#endif //SNAKESFML_WINDOW_H