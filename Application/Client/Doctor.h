#pragma once
#include "../../Server/include/Patient.h"
#include <random>

class Doctor{
private:
    Patient _patient;
    Visit visit;
    string SetAnamnes(){
        const char* patientComplaints[15] = {
            "I'm feeling very tired all the time.",
            "I have a persistent headache.",
            "My stomach hurts after eating.",
            "I can't sleep well at night.",
            "I've been feeling anxious lately.",
            "I have a cough that won't go away.",
            "I feel dizzy when I stand up.",
            "My joints are aching.",
            "I have a rash that itches.",
            "I've lost my appetite.",
            "I'm experiencing shortness of breath.",
            "I have a sore throat.",
            "I feel nauseous after taking my medication.",
            "I have frequent mood swings.",
            "I'm having trouble concentrating."
        };
        int random = rand() % 15;
        visit.anamn = patientComplaints[random];
        return visit.anamn;
    }
public:
    Doctor() : _patient(1, "Orehov", "Nikita", "Antonobich", man){}

    void AppendDrug(vector<int> drugsInt){
        for (auto f: drugsInt){
            switch (f){
                case 1: visit.drugs.push_back("Aspirin"); break;
                case 2: visit.drugs.push_back("Ibuprofen"); break;
                case 3: visit.drugs.push_back("Acetaminophen"); break;
                case 4: visit.drugs.push_back("Amoxicillin"); break;
                case 5: visit.drugs.push_back("Metformin"); break;
                case 6: visit.drugs.push_back("Lisinopril"); break;
                case 7: visit.drugs.push_back("Simvastatin"); break;
                case 8: visit.drugs.push_back("Omeprazole"); break;
                case 9: visit.drugs.push_back("Levothyroxine"); break;
                case 10: visit.drugs.push_back("Atorvastatin"); break;
                default: break;
            }
        }
    }

    void AppendHealthScript(string script){
        visit.ms = script;
    }

    std::string SetPatient(Patient pat){
        _patient = pat;
        return SetAnamnes();
    }

    Patient GetPatient(){ 
        _patient.AddVisit(visit);
        return _patient;
    }
};