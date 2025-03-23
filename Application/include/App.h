#pragma once
#include "ConnectHandler.h"
#include "MessageWindow.h"
#include "Input.h"
#include "InputDrugs.h"
#include "Historyes.h"

class App{
private:
    ConnectHandler _con;
    Doctor _doc;
    sf::RenderWindow _window;
    Button _next;
    Button _update;
    sf::Font _font;
    Input _inputHS;
    InputDrugs _inputDrugs;
    Histyes _historyes;

    bool NextOrUpdate = 0;

    sf::Text PatText;
    sf::Text NameText;
    sf::Text SurnameText;
    sf::Text PatronText;
    sf::Text GenderText;
    sf::Text AnamnesText;

    sf::Text NamePat;
    sf::Text SurnamePat;
    sf::Text PatronPat;
    sf::Text GenderPat;
    sf::Text AnamnesPat;

public:
    App();

    void Start();

    void updateMain();

    void ButtonNext();

    void ButtonUpdate();
};