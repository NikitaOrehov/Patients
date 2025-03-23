#pragma once
#include <SFML/Graphics.hpp>
#include "../Doctor.h"
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
    Histyes() : _nextButton(800, 350, 150, 50, "next"), _previousButton(600, 350, 150, 50, "previous"), _closeButton(600, 380, 150, 50, "close"){
        if (!_font.loadFromFile("/home/kinro/project/Patients/Client/RobotoMono-VariableFont_wght.ttf")) {
            std::cerr << "Error loading font" << std::endl;
        }

        _text.setString("Historyes:");
        _text.setFont(_font);
        _text.setFillColor(sf::Color::Black);
        _text.setCharacterSize(25);
        _text.setPosition(600, 70);

        textDrugs.setString("Drugs: ");
        textDrugs.setFont(_font);
        textDrugs.setFillColor(sf::Color::Black);
        textDrugs.setCharacterSize(25);
        textDrugs.setPosition(600, 110);

        textAnamnes.setString("Anamnes: ");
        textAnamnes.setFont(_font);
        textAnamnes.setFillColor(sf::Color::Black);
        textAnamnes.setCharacterSize(25);
        textAnamnes.setPosition(600, 190);

        textHS.setString("Health Script: ");
        textHS.setFont(_font);
        textHS.setFillColor(sf::Color::Black);
        textHS.setCharacterSize(25);
        textHS.setPosition(600, 270);

        PatAnamnes.setFont(_font);
        PatAnamnes.setFillColor(sf::Color::Black);
        PatAnamnes.setCharacterSize(25);
        PatAnamnes.setPosition(620, 150);

        PatDrugs.setFont(_font);
        PatDrugs.setFillColor(sf::Color::Black);
        PatDrugs.setCharacterSize(25);
        PatDrugs.setPosition(620, 230);

        PatHS.setFont(_font);
        PatHS.setFillColor(sf::Color::Black);
        PatHS.setCharacterSize(25);
        PatHS.setPosition(620, 310);   
        
        tmp.setFont(_font);
        tmp.setFillColor(sf::Color::Black);
        tmp.setCharacterSize(25); 
    }

    void SetVisits(vector<Visit> historyes){
        _size = historyes.size();
        _historyes = historyes;
        _shapes = new sf::RectangleShape[_size];
        for (int i = 0; i < _size; i++){
            _shapes[i].setSize(sf::Vector2f(150, 50));
            _shapes[i].setFillColor(sf::Color::Red);
        }
    }

    void draw(sf::RenderWindow& window){
        window.draw(_text);
        if (_status == -1){
            return;
        }

        if (patient != -1){
            PatHS.setString(_historyes[patient].ms);
            PatAnamnes.setString(_historyes[patient].anamn);
            string drugs;
            for (int i = 0; i < _historyes[patient].drugs.size(); i++){
                drugs += _historyes[patient].drugs[i];
                drugs += " ";
            }
            PatDrugs.setString(drugs);
            window.draw(textAnamnes);
            window.draw(textDrugs);
            window.draw(textHS);
            window.draw(PatAnamnes);
            window.draw(PatHS);
            window.draw(PatDrugs);
            _closeButton.draw(window);
            return;
        }

        int end;
        if (0 + (_status + 1) * 3 >= _size) end = _size;
        else if (_status == 0) end = 0 + (_status + 1) * 3;
        else end = 0 + (_status + 1) * 3;
        for (int i = 0 + _status * 3; i < end; i++){
            _shapes[i].setPosition(sf::Vector2f(600, (100 + (i % 3) * 50) + 3 * (i % 3) + 30));
            string tmpStr = "number " + to_string(i + 1);
            tmp.setString(tmpStr);
            tmp.setPosition(sf::Vector2f(600, (100 + (i % 3) * 50) + 3 * (i % 3) + 30));
            window.draw(_shapes[i]);
            window.draw(tmp);
        }
        _nextButton.draw(window);
        _previousButton.draw(window);
    }


    void IsMouseOver(sf::RenderWindow& window){
        int end;
        if (0 + (_status + 1) * 3 >= _size) end = _size;
        else end  = 0 + (_status + 1) * 3;

        if (_status >= 0){
            for (int i = 0 + _status * 3; i < end; i++){
                if (_shapes[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                    patient = i;
                    return;
                }
            }
        }
        
        if (_nextButton.isMouseOver(window)){
            if ((_status + 1) * 3 < _size) _status += 1;
        }
        if (_previousButton.isMouseOver(window)){
            if (_status > 0 ) _status -= 1;
        }
        if (_closeButton.isMouseOver(window)){
            patient = -1;
        }
    }

    void Setstatus(int status){_status = status;}

};