#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class InputDrugs{
private:
    sf::Text _text;
    sf::RectangleShape _shapes[10];
    sf::Font _font;
    bool _status[10];

    sf::Text _text1;
    sf::Text _text2;
    sf::Text _text3;
    sf::Text _text4;
    sf::Text _text5;
    sf::Text _text6;
    sf::Text _text7;
    sf::Text _text8;
    sf::Text _text9;
    sf::Text _text10;
public:
    InputDrugs(float x, float y, float width, float height);

    void draw(sf::RenderWindow& window);

    void IsMouseOver(sf::RenderWindow& window);

    std::vector<int> GetStatus();

    void Reset();
};