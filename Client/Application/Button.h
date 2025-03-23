#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button{
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
public:
    Button(float x, float y, float width, float height, const std::string& Text) {
        shape.setSize(sf::Vector2(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);

        if (!font.loadFromFile("/home/kinro/project/Patients/Client/RobotoMono-VariableFont_wght.ttf")) {
            std::cerr << "Error loading font" << std::endl;
        }

        text.setFont(font);
        text.setString(Text);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::Black);
        text.setPosition(
            x + (width - text.getGlobalBounds().width) / 2,
            y + (height - text.getGlobalBounds().height) / 2
        );
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        return shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }
};