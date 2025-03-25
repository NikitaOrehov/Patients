#include "App.h"

App::App(): _window(sf::RenderWindow(sf::VideoMode(1100, 1500), "Doctor")), _next(100, 900, 150, 50, "next"), _update(850, 900, 150, 50, "update"), _inputHS(30, 550, 500, 150, "HealthScript"), _inputDrugs(850, 500, 200, 30){
    if (!_font.loadFromFile(path_font_sample)){//500 150
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    PatText.setString("Patient");
    PatText.setFont(_font);
    PatText.setFillColor(sf::Color::Black);
    PatText.setCharacterSize(25);
    PatText.setPosition(30, 50);

    NameText.setString("Name: ");
    NameText.setFont(_font);
    NameText.setFillColor(sf::Color::Black);
    NameText.setCharacterSize(25);
    NameText.setPosition(30, 100);

    SurnameText.setString("Surname: ");
    SurnameText.setFont(_font);
    SurnameText.setFillColor(sf::Color::Black);
    SurnameText.setCharacterSize(25);
    SurnameText.setPosition(30, 150);

    PatronText.setString("Patron: ");
    PatronText.setFont(_font);
    PatronText.setFillColor(sf::Color::Black);
    PatronText.setCharacterSize(25);
    PatronText.setPosition(30, 200);

    GenderText.setString("Gender: ");
    GenderText.setFont(_font);
    GenderText.setFillColor(sf::Color::Black);
    GenderText.setCharacterSize(25);
    GenderText.setPosition(30, 250);

    AnamnesText.setString("Anamnes: ");
    AnamnesText.setFont(_font);
    AnamnesText.setFillColor(sf::Color::Black);
    AnamnesText.setCharacterSize(25);
    AnamnesText.setPosition(30, 300);

    NamePat.setFont(_font);
    NamePat.setFillColor(sf::Color::Black);
    NamePat.setCharacterSize(25);
    NamePat.setPosition(150, 100);

    SurnamePat.setFont(_font);
    SurnamePat.setFillColor(sf::Color::Black);
    SurnamePat.setCharacterSize(25);
    SurnamePat.setPosition(150, 150);

    PatronPat.setFont(_font);
    PatronPat.setFillColor(sf::Color::Black);
    PatronPat.setCharacterSize(25);
    PatronPat.setPosition(150, 200);

    GenderPat.setFont(_font);
    GenderPat.setFillColor(sf::Color::Black);
    GenderPat.setCharacterSize(25);
    GenderPat.setPosition(150, 250);

    AnamnesPat.setFont(_font);
    AnamnesPat.setFillColor(sf::Color::Black);
    AnamnesPat.setCharacterSize(25);
    AnamnesPat.setPosition(150, 300);
}

void App::Start(){
    while(_window.isOpen()){
        _con.Connect();
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
            if (event.type == sf::Event::TextEntered){
                if (_inputHS.status){
                    _inputHS.AddChar(static_cast<char>(event.text.unicode));
                }
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if (NextOrUpdate){
                    if (_inputHS.IsMouseOver(_window)) _inputHS.status = 1;
                    else _inputHS.status = 0;
                    _inputDrugs.IsMouseOver(_window);
                }
                if (_next.isMouseOver(_window)){
                    try{
                        ButtonNext(); 
                    }
                    catch(const char* message){
                        std::cout<<message<<"\n";
                        MessageWindow _messageWindow(message);
                        _messageWindow.Start();

                    }
                }
                else if (_update.isMouseOver(_window)){
                    try{
                        ButtonUpdate();
                    }
                    catch(const char* message){
                        std::cout<<message<<"\n";
                        MessageWindow _messageWindow(message);
                        _messageWindow.Start();
                    }
                }
                _historyes.IsMouseOver(_window);
            }


        }
        updateMain();
        _con.Disconnect();
    }
}

void App::updateMain(){
    _window.clear(sf::Color::Cyan);

    _next.draw(_window);
    _inputHS.draw(_window);
    _inputDrugs.draw(_window);
    _update.draw(_window);
    _historyes.draw(_window);

    _window.draw(PatText);
    _window.draw(NameText);
    _window.draw(SurnameText);
    _window.draw(PatronText);
    _window.draw(GenderText);
    _window.draw(AnamnesText);
    
    _window.draw(NamePat);
    _window.draw(SurnamePat);
    _window.draw(PatronPat);
    _window.draw(GenderPat);
    _window.draw(AnamnesPat);

    _window.display();
}

void App::ButtonNext(){
    if (!NextOrUpdate) NextOrUpdate = 1;
    Patient patient = _con.GetPatient();
    NamePat.setString(patient._Name);
    SurnamePat.setString(patient._Surname);
    PatronPat.setString(patient._Patron);
    if (patient._Gender == man){
        GenderPat.setString("Man");
    }
    else{
        GenderPat.setString("Woman");
    }
    AnamnesPat.setString(_doc.SetPatient(patient));
    _historyes.SetVisits(patient._History);
    _historyes.Setstatus(0);
    return;

}

void App::ButtonUpdate(){
    if (NextOrUpdate) NextOrUpdate = 0;
    else return;
    _historyes.Setstatus(-1);

    _doc.AppendDrug(_inputDrugs.GetStatus());
    _doc.AppendHealthScript(_inputHS.GetString());

    _con.UpdatePatient(_doc.GetPatient());

    NamePat.setString("");
    SurnamePat.setString("");
    PatronPat.setString("");
    GenderPat.setString("");
    AnamnesPat.setString("");

    _inputDrugs.Reset();
    _inputHS.Reset();
}