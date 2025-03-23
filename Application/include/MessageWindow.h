#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "../files/path.h"

class MessageWindow{
private:
    sf::RenderWindow _window;
    std::string str;
    sf::Font _font;
    sf::Text _text;
public:
    MessageWindow(std::string text) : _window(sf::RenderWindow(sf::VideoMode(500, 300), "Message")){
        _window.setPosition(sf::Vector2(500, 500));
        if (!_font.loadFromFile(path_font_sample)) {
            std::cerr << "Error loading font" << std::endl;
        }
        std::cout<<str<<"\n";
        str = text;
        _text.setString(str);
        _text.setFont(_font);
        _text.setFillColor(sf::Color::Black);
        _text.setCharacterSize(25);
        _text.setPosition(sf::Vector2f(150, 150));
    }

    void Start(){
        while (_window.isOpen()){
            sf::Event event;
            while (_window.pollEvent(event)){
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
            }
            Update();
        }
    }

    void Update(){
        _window.clear(sf::Color::Cyan);
        _window.draw(_text);
        _window.display();
    }
};