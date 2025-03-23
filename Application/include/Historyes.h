#pragma once
#include <SFML/Graphics.hpp>
#include "Doctor.h"
#include "Button.h"
#include <vector>
#include <cstring>

class Histyes{
private:
    sf::Text _text;
    sf::Font _font;
    Button _nextButton;
    Button _previousButton;
    Button _closeButton;
    sf::RectangleShape* _shapes;
    size_t _size;
    int _status = -1;
    int patient = -1;
    vector<Visit> _historyes;

    sf::Text tmp;
    sf::Text textDrugs;
    sf::Text textAnamnes;
    sf::Text textHS;
    sf::Text PatDrugs;
    sf::Text PatAnamnes;
    sf::Text PatHS;
public:
    Histyes();

    void SetVisits(vector<Visit> historyes);

    void draw(sf::RenderWindow& window);

    void IsMouseOver(sf::RenderWindow& window);

    void Setstatus(int status);

};