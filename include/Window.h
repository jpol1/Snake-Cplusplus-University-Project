#ifndef SNAKESFML_WINDOW_H
#define SNAKESFML_WINDOW_H
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"

void drawGrid(sf::RenderWindow& window);
void runGame(sf::RenderWindow& window, sf::Clock& clock, Snake& snake, Apple& apple);
void drawCounter(sf::RenderWindow& window);
void drawGameOver(sf::RenderWindow& window, int snakeSize, int bestScore);
int loadBestScore(const std::string& filename);
void saveBestScore(int score, const std::string& filename);
void loadMenu(sf::RenderWindow& window);

#endif //SNAKESFML_WINDOW_H