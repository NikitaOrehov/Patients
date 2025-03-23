#include "InputDrugs.h"

InputDrugs::InputDrugs(float x, float y, float width, float height){
    if (!_font.loadFromFile("/home/kinro/project/Patients/Application/files/RobotoMono-Italic-VariableFont_wght.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    _text.setString("drugs");
    _text.setFont(_font);
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(25);
    _text.setPosition(x, y - 10);

    _text1.setString("Aspirin");
    _text1.setFont(_font);
    _text1.setFillColor(sf::Color::Black);
    _text1.setCharacterSize(25);
    _text1.setPosition(sf::Vector2(x, (y + 0 * height) + 5 * 0 + 30));

    _text2.setString("Ibuprofen");
    _text2.setFont(_font);
    _text2.setFillColor(sf::Color::Black);
    _text2.setCharacterSize(25);
    _text2.setPosition(sf::Vector2(x, (y + 2 * height) + 5 * 2 + 30));

    _text3.setString("Acetaminophen");
    _text3.setFont(_font);
    _text3.setFillColor(sf::Color::Black);
    _text3.setCharacterSize(25);
    _text3.setPosition(sf::Vector2(x, (y + 3 * height) + 5 * 3 + 30));

    _text4.setString("Amoxicillin");
    _text4.setFont(_font);
    _text4.setFillColor(sf::Color::Black);
    _text4.setCharacterSize(25);
    _text4.setPosition(sf::Vector2(x, (y + 4 * height) + 5 * 4 + 30));

    _text5.setString("Metformin");
    _text5.setFont(_font);
    _text5.setFillColor(sf::Color::Black);
    _text5.setCharacterSize(25);
    _text5.setPosition(sf::Vector2(x, (y + 5 * height) + 5 * 5 + 30));

    _text6.setString("Lisinopril");
    _text6.setFont(_font);
    _text6.setFillColor(sf::Color::Black);
    _text6.setCharacterSize(25);
    _text6.setPosition(sf::Vector2(x, (y + 6 * height) + 5 * 6 + 30));

    _text7.setString("Simvastatin");
    _text7.setFont(_font);
    _text7.setFillColor(sf::Color::Black);
    _text7.setCharacterSize(25);
    _text7.setPosition(sf::Vector2(x, (y + 7 * height) + 5 * 7 + 30));

    _text8.setString("Omeprazole");
    _text8.setFont(_font);
    _text8.setFillColor(sf::Color::Black);
    _text8.setCharacterSize(25);
    _text8.setPosition(sf::Vector2(x, (y + 8 * height) + 5 * 8 + 30));

    _text9.setString("Levothyroxine");
    _text9.setFont(_font);
    _text9.setFillColor(sf::Color::Black);
    _text9.setCharacterSize(25);
    _text9.setPosition(sf::Vector2(x, (y + 9 * height) + 5 * 9 + 30));

    _text10.setString("Atorvastatin");
    _text10.setFont(_font);
    _text10.setFillColor(sf::Color::Black);
    _text10.setCharacterSize(25);
    _text10.setPosition(sf::Vector2(x, (y + 1 * height) + 5 * 1 + 30));

    for(int i = 0; i < 10; i++){
        _shapes[i].setSize(sf::Vector2(width, height));
        _shapes[i].setPosition(sf::Vector2(x, (y + i * height) + 5 * i + 30));
        _shapes[i].setFillColor(sf::Color::White);
    }
}

void InputDrugs::draw(sf::RenderWindow& window){
    window.draw(_text);
    for (int i = 0; i < 10; i++){
        window.draw(_shapes[i]);
    }
    window.draw(_text1);
    window.draw(_text2);
    window.draw(_text3);
    window.draw(_text4);
    window.draw(_text5);
    window.draw(_text6);
    window.draw(_text7);
    window.draw(_text8);
    window.draw(_text9);
    window.draw(_text10);
}

void InputDrugs::IsMouseOver(sf::RenderWindow& window){
    for (int i = 0; i < 10; i++){
        if (_shapes[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
            if (_status[i]){
                _shapes[i].setFillColor(sf::Color::White);
                _status[i] = 0;
            }
            else{
                _shapes[i].setFillColor(sf::Color::Yellow);
                _status[i] = 1;
            }
        }
    }
}

std::vector<int> InputDrugs::GetStatus(){
    std::vector<int> res;
    for (int i = 0; i < 10; i++){
        if (_status[i] == 1){
            res.push_back(i + 1);
        }
    }
    return res;
}

void InputDrugs::Reset() {
    for (int i = 0; i < 10; i++){
        _status[i] = 0;
        _shapes[i].setFillColor(sf::Color::White);
    }
}