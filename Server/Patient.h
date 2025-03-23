#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Gender {man, woman};

struct Visit{
    string anamn;
    string ms;
    vector<string> drugs;
    string ToStr(){
        string res = "%" + anamn + "&" + ms;
        for (int i = 0; i< drugs.size(); i++){
            res += "&" + drugs[i];
        }
        res += "%";
        return res;
    }
};


class App;

class Patient{
private:
    size_t _id;
    string _Surname;
    string _Name;
    string _Patron;
    Gender _Gender;
    vector<Visit> _History;
public:
    Patient(int id, string Surname, string Name, string Patron, Gender Gender) : _id(id), _Surname(Surname), _Name(Name), _Patron(Patron), _Gender(Gender){}
    friend class App;
    
    string Tostr(){
        string res = to_string(_id) + "|" + _Surname + "|" +_Name + "|" + _Patron + "|";
        if (_Gender == man) res += "m|";
        else res += "w|";
        for (int i = 0; i < _History.size(); i++){
            res += _History[i].ToStr();
        }
        return res;
    }

    Patient(string str){
        string word;
        int i = 0;
        int count = 0;
        while (count != 5){
            if (str[i] == '|'){
                i++;
                count++;
                switch (count){
                    case 1: _id = std::stoi(word); word.clear(); break;
                    case 2: _Surname = word; word.clear(); break;
                    case 3: _Name = word; word.clear(); break;
                    case 4: _Patron = word; word.clear(); break;
                    case 5: if (word == "m") {_Gender = man; word.clear(); break;} else {_Gender = woman; word.clear(); break;}
                    default: break;
                }
            }
            else{
                word += str[i];
                i++;
            }
        }
        count = 0;
        i++;
        while (i <= str.size()){
            Visit vis;
            while (str[i] != '%'){
                if (str[i] == '&'){
                    i++;
                    count++;
                    switch (count){
                        case 1: vis.anamn = word; word.clear(); break;
                        case 2: vis.ms = word; word.clear(); break;
                        default: vis.drugs.push_back(word); word.clear(); break;
                    }
                }
                word += str[i];
                i++;
            }
            count = 0;
            vis.drugs.push_back(word);
            word.clear();
            _History.push_back(vis);
            char c = str[i];
            i += 2;
        }
    }

    void AddVisit(Visit vis){
        _History.push_back(vis);
    }

    Visit pop_back(){return _History.back();}

    friend std::ostream& operator<<(std::ostream& os, Patient pat){
        std::cout<<"Surname: "<<pat._Surname<<"\n";
        std::cout<<"Name: "<<pat._Name<<"\n";
        std::cout<<"Patron: "<<pat._Patron<<"\n";
        std::cout<<"Gender: "<<pat._Gender<<"\n";
        std::cout<<"--------------------------\n";
        for (int i = 0; i < pat._History.size(); i++){
            std::cout<<"Anamnes: "<<pat._History[i].anamn<<"\n";
            std::cout<<"MS: "<<pat._History[i].ms<<"\n";
            for (int j = 0; j < pat._History[i].drugs.size(); j++){
                std::cout<<"Drugs: "<<pat._History[i].drugs[j]<<"\n";
            }
            std::cout<<"--------------------------\n";
        }
        return os;
    }    
};