#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <exception>

class Input{
private:
    sf::RectangleShape _shape;
    std::string _textStr;
    sf::Text _title;
    sf::Text _text;
    sf::Font _font;
    sf::Texture _texture;
public:
    bool status;
    Input(float x, float y, float width, float height, std::string title) : _shape(sf::Vector2(width, height)){

        _shape.setPosition(x, y);

        if (!_font.loadFromFile("/home/kinro/project/Patients/Client/RobotoMono-VariableFont_wght.ttf")) {
            std::cerr << "Error loading font" << std::endl;
        }
        _text.setFont(_font);
        _text.setFillColor(sf::Color::Black);
        _text.setCharacterSize(25);
        _text.setPosition(x + 15, y + 3);

        _title.setString(title);
        _title.setFont(_font);
        _title.setFillColor(sf::Color::Black);
        _title.setCharacterSize(25);
        _title.setPosition(x, y - 30);

        if (!_texture.loadFromFile("/home/kinro/project/Patients/Client/Application/foni-papik-pro-l0h4-p-kartinki-pryamougolnik-na-prozrachnom-fone-7.png")) { // Убедитесь, что путь к текстуре корректный
            std::cerr << "Error loading texture" << std::endl;
            return;
        }
        _shape.setTexture(&_texture);
    }

    bool IsMouseOver(sf::RenderWindow& window){
        return _shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }

    void AddChar(char sym){
        if (sym == 8){
            if (_textStr.size() > 0){
                _textStr.pop_back();
                _text.setString(_textStr);
                return;
            }
        }
        if(_textStr.size() == 31 || _textStr.size() == 63 || _textStr.size() == 95 || _textStr.size() == 127){
            _textStr += '\n';
        }
        if (_textStr.size() == 128){
            return;
        }
        _textStr += sym;
        _text.setString(_textStr);
    }

    void draw(sf::RenderWindow& window){
        window.draw(_shape);
        window.draw(_text);
        window.draw(_title);
    }

    std::string GetString(){return _textStr;}
    void Reset(){_textStr.clear(); _text.setString(_textStr);}
};