#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Snake");

    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}