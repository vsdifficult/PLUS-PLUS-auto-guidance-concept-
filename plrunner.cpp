#include <SFML/Graphics.hpp>
#include <cmath>

class Character {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Character() : shape(30.f) {
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(30.f, 30.f);
        shape.setPosition(100.f, 100.f);
        velocity = sf::Vector2f(0.f, 0.f);
    }

    void updatePosition(const sf::Vector2f& targetPos) {
        // Calculate direction to the target
        sf::Vector2f direction = targetPos - shape.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalize the direction
        direction /= length;

        // Update velocity based on the direction
        velocity = direction * 2.f;

        // Update position based on velocity
        shape.move(velocity);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Autonomous Navigation");

    Character character;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        character.updatePosition(mousePos);

        window.clear(sf::Color::White);
        window.draw(character.shape);
        window.display();
    }

    return 0;
}
