#include "../include/Window.h"

#include <SFML/Graphics.hpp>
#include "../include/Constants.h"
#include "../include/Direction.h"
#include "../include/Snake.h"
#include "../include/Apple.h"
#include "../include/GameState.h"
#include <fstream>
#include <iostream>
int loadBestScore(const std::string& filename="../assets/data/best_score.txt") {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot open file with best score\n";
        return 0;
    }

    int bestScore = 0;
    file >> bestScore;

    return bestScore;
}

void saveBestScore(const int score, const std::string& filename="../assets/data/best_score.txt") {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot save best score\n";
        return;
    }

    file << score;
}

void loadMenu(sf::RenderWindow &window, int selectedOption=0) {
    sf::Font font;

    if (!font.openFromFile("../assets/fonts/Comic Sans MS.ttf")) {
        std::cout << "Failed to load font\n";
    };

    sf::Text title(font);
    title.setString("AGH C++ SNAKE");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color(30,120,240));

    auto titleBounds = title.getLocalBounds();
    title.setPosition({
        WINDOW_WIDTH / 2.f - titleBounds.size.x / 2.f,
        WINDOW_HEIGHT / 2.f - titleBounds.size.y / 2.f - 240
    });

    sf::Text play(font);
    play.setString("PLAY");
    play.setCharacterSize(50);
    if (selectedOption == 0) {
        play.setFillColor(sf::Color::Magenta);
    }
    else {
        play.setFillColor(sf::Color::White);
    }
    play.setPosition({
        title.getPosition().x,
        title.getPosition().y + 100
    });

    sf::Text rules(font);
    rules.setString("GAME RULES");
    rules.setCharacterSize(50);
    if (selectedOption == 1) {
        rules.setFillColor(sf::Color::Magenta);
    }
    else {
        rules.setFillColor(sf::Color::White);
    }
    rules.setPosition({
        play.getPosition().x,
        play.getPosition().y + 40
    });

    sf::Text exit(font);
    exit.setString("EXIT");
    exit.setCharacterSize(50);
    if (selectedOption == 2) {
        exit.setFillColor(sf::Color::Magenta);
    }
    else {
        exit.setFillColor(sf::Color::White);
    }
    exit.setPosition({
        rules.getPosition().x,
        rules.getPosition().y + 40
    });


    window.draw(title);
    window.draw(play);
    window.draw(rules);
    window.draw(exit);
}

void drawGrid(sf::RenderWindow& window){
    sf::RectangleShape verticalLine(sf::Vector2f(1, WINDOW_HEIGHT));
    verticalLine.setFillColor(sf::Color(40,40,40));

    sf::RectangleShape horizontalLine(sf::Vector2f(WINDOW_WIDTH, 1));
    horizontalLine.setFillColor(sf::Color(40,40,40));

    for (int x = 0; x <= 800; x += 20) {
        verticalLine.setPosition(sf::Vector2f(static_cast<float>(x),0.f));
        window.draw(verticalLine);
    }

    for (int y = 0; y <= 600; y += 20) {
        horizontalLine.setPosition(sf::Vector2f(0.f, static_cast<float>(y)));
        window.draw(horizontalLine);
    }
}

void drawCounter(sf::RenderWindow& window, int snakeSize) {
    sf::Font font;
    if (!font.openFromFile("../assets/fonts/Comic Sans MS.ttf")) {
        std::cout << "Failed to load font\n";
    };

    sf::Text text(font);
    text.setString(std::to_string(snakeSize-2));
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition({760 , 20});
    window.draw(text);
}

void drawGameOver(sf::RenderWindow& window, int snakeSize, int bestScore) {
    sf::Font font;

    if (!font.openFromFile("../assets/fonts/Comic Sans MS.ttf")) {
        std::cout << "Failed to load font\n";
    };

    sf::Text title(font);
    title.setString("GAME OVER");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color(120,0,0));

    auto titleBounds = title.getLocalBounds();
    title.setPosition({
        WINDOW_WIDTH / 2.f - titleBounds.size.x / 2.f,
        WINDOW_HEIGHT / 2.f - titleBounds.size.y / 2.f - 120
    });

    sf::Text score(font);
    score.setString("Your score: " + std::to_string(snakeSize-2));
    score.setCharacterSize(50);
    score.setFillColor(sf::Color::White);
    score.setPosition({
        title.getPosition().x,
        title.getPosition().y + 100
    });


    sf::Text restart(font);
    restart.setString("Click R to Restart");
    restart.setCharacterSize(30);
    restart.setFillColor(sf::Color::White);
    restart.setPosition({
        title.getPosition().x,
        title.getPosition().y + 180
    });

    sf::Text menu(font);
    menu.setString("Click Esc to return to the menu");
    menu.setCharacterSize(30);
    menu.setFillColor(sf::Color::White);
    menu.setPosition({
        restart.getPosition().x,
        restart.getPosition().y + 40
    });

    sf::Text best_score(font);
    best_score.setString("Best score: " + std::to_string(bestScore));
    best_score.setCharacterSize(20);
    best_score.setFillColor(sf::Color::White);
    best_score.setPosition({
        10,
        10
    });

    window.draw(title);
    window.draw(score);
    window.draw(restart);
    window.draw(menu);
    window.draw(best_score);
}

void drawRules(sf::RenderWindow& window) {
    sf::Font font;

    if (!font.openFromFile("../assets/fonts/Comic Sans MS.ttf")) {
        std::cout << "Failed to load font\n";
    };

    sf::Text title(font);
    title.setString("HOW TO PLAY SNAKE");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);

    auto titleBounds = title.getLocalBounds();
    title.setPosition({
        WINDOW_WIDTH / 2.f - titleBounds.size.x / 2.f,
        WINDOW_HEIGHT / 2.f - titleBounds.size.y / 2.f - 240
    });

    sf::Text how_play(font);
    how_play.setCharacterSize(20);
    how_play.setString(
    "• Use arrow keys to control the snake.\n"
    "• You have only one life.\n"
    "• Collect as many apples as possible.\n"
    "• Each apple increases your score.\n"
    "• The snake gets faster after every apple.\n"
    "• Do not hit the walls.\n"
    "• Do not run into your own body.\n"
    "• One mistake ends the game.\n"
    "• Press esc to pause."
    );
    how_play.setFillColor(sf::Color::White);
    how_play.setPosition({
        title.getPosition().x + 100,
        title.getPosition().y + 150
    });

    sf::Text return_key(font);
    return_key.setCharacterSize(15);
    return_key.setString(
    "Press ESC to return to the menu"
    );
    return_key.setFillColor(sf::Color::White);
    return_key.setPosition({30 , 550});

    window.draw(how_play);
    window.draw(return_key);
    window.draw(title);
}

void drawPause(sf::RenderWindow& window, const int snakePoints) {
    sf::Font font;

    if (!font.openFromFile("../assets/fonts/Comic Sans MS.ttf")) {
        std::cout << "Failed to load font\n";
    };

    sf::RectangleShape rec(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 4.f));
    rec.setFillColor(sf::Color::Black);
    rec.setPosition({
    WINDOW_WIDTH / 2.f - rec.getSize().x / 2.f,
    WINDOW_HEIGHT / 2.f - rec.getSize().y / 2.f
    });

    sf::Text scores(font);
    std::string actScore = std::to_string(snakePoints);
    scores.setString("Your score: " + actScore);
    scores.setCharacterSize(20);
    scores.setFillColor(sf::Color::White);
    scores.setPosition({rec.getPosition().x + 40, rec.getPosition().y + 40});

    sf::Text playing(font);
    playing.setString("Click Esc to return to the game!");
    playing.setCharacterSize(20);
    playing.setFillColor(sf::Color::White);
    playing.setPosition({
        scores.getPosition().x,
        scores.getPosition().y + 40
    });

    window.draw(rec);
    window.draw(playing);
    window.draw(scores);
}

void runGame(sf::RenderWindow& window, sf::Clock& clock, Snake& snake, Apple& apple) {
    GAME_STATE game_state = GAME_STATE::MENU;
    int bestScore = loadBestScore();
    int game_state_number = 0;
    while (window.isOpen()) {
        window.clear();
        if (game_state == GAME_STATE::MENU) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
                if (event->is<sf::Event::KeyPressed>()) {
                    auto key = event->getIf<sf::Event::KeyPressed>();

                    if (key->code == sf::Keyboard::Key::Up) {
                        game_state_number = (game_state_number - 1 + 3) % 3;
                    }
                    else if (key->code == sf::Keyboard::Key::Down) {
                        game_state_number = (game_state_number + 1) % 3;
                    }
                    else if (key->code == sf::Keyboard::Key::Enter) {
                        if (game_state_number == 0) {
                            game_state = GAME_STATE::PLAYING;
                            snake = Snake();
                        }
                        else if (game_state_number == 1) {
                            game_state = GAME_STATE::HOW_TO_PLAY;
                        }
                        else if (game_state_number == 2) {
                            window.close();
                        }
                    }
                }
            }
            loadMenu(window, game_state_number);
        }


        else if (game_state == GAME_STATE::PLAYING) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
                if (event->is<sf::Event::KeyPressed>()) {
                    auto key = event->getIf<sf::Event::KeyPressed>();

                    if (key->code == sf::Keyboard::Key::Left) {
                        snake.setSnakeDirection(DIRECTION::LEFT);
                    }
                    else if (key->code == sf::Keyboard::Key::Right) {
                        snake.setSnakeDirection(DIRECTION::RIGHT);
                    }
                    else if (key->code == sf::Keyboard::Key::Up) {
                        snake.setSnakeDirection(DIRECTION::UP);
                    }
                    else if (key->code == sf::Keyboard::Key::Down) {
                        snake.setSnakeDirection(DIRECTION::DOWN);
                    }
                    else if (key->code == sf::Keyboard::Key::Escape) {
                        game_state = GAME_STATE::PAUSE;
                    }
                }
            }
            if (clock.getElapsedTime().asSeconds() >= snake.snakeSpeed()) {
                sf::Vector2i tmp_tail = snake.tail();
                snake.moveSnake();

                if (snake.headX() == apple.AppleX() && snake.headY() == apple.AppleY()) {
                    snake.increaseSnake(tmp_tail);
                    snake.increaseSpeed();

                    do {
                        apple.randomizePosition();
                    } while (apple.positionInSnake(snake));
                }

                snake.setAlive();
                if (!snake.isAlive()) {
                    game_state = GAME_STATE::GAME_OVER;

                    if (snake.bodySize() - 2 > bestScore) {
                        bestScore = snake.bodySize() - 2;
                        saveBestScore(bestScore);
                    }
                }
                clock.restart();
            }
            drawGrid(window);
            apple.drawApple(window);
            snake.drawSnake(window);
            drawCounter(window, snake.bodySize());
        }

        else if (game_state == GAME_STATE::PAUSE) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
                if (event->is<sf::Event::KeyPressed>()) {
                    auto key = event->getIf<sf::Event::KeyPressed>();

                    if (key->code == sf::Keyboard::Key::Escape) {
                        game_state = GAME_STATE::PLAYING;
                    }
                }
            }
            drawGrid(window);
            apple.drawApple(window);
            snake.drawSnake(window);
            drawPause(window, snake.bodySize() - 2);
        }

        else if (game_state == GAME_STATE::HOW_TO_PLAY) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                if (event->is<sf::Event::KeyPressed>()) {
                    auto key = event->getIf<sf::Event::KeyPressed>();

                    if (key->code == sf::Keyboard::Key::Escape) {
                        game_state = GAME_STATE::MENU;
                    }
                }
            }
            drawRules(window);
        }
        else if (game_state == GAME_STATE::GAME_OVER) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                if (event->is<sf::Event::KeyPressed>()) {
                    auto key = event->getIf<sf::Event::KeyPressed>();

                    if (key->code == sf::Keyboard::Key::R) {
                        snake = Snake();
                        do {
                            apple.randomizePosition();
                        } while (apple.positionInSnake(snake));

                        bestScore = loadBestScore();
                        game_state = GAME_STATE::PLAYING;
                    }
                    else if (key->code == sf::Keyboard::Key::Escape) {
                        game_state = GAME_STATE::MENU;
                    }
                }
            }
            drawGameOver(window, snake.bodySize(), bestScore);
        }
        window.display();
    }
}