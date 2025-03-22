#pragma once
#include "Queue.h"
#include "DataBaseWorker.h"

class PatientController{
private:
    Queue<Patient> _patients;
    DataBaseWorker _dbController;
public:
    PatientController(){
        vector<Patient> patients = _dbController.GetList();
        for (int i = 0; i < patients.size(); i++){
            _patients.Push(patients[i]);
        }
    }

    Patient Next(){
        Patient pat = _patients.Front();
        _patients.Pop();
        return pat;
    }
    
    void UpdatePatient(Patient _patient){
        _dbController.Update(_patient);
        return;
    }
};