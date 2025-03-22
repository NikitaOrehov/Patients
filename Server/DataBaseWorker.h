#pragma once
#include <string>
#include <vector>
#include "Patient.h"

using namespace std;

class DataBaseWorker{
private:
public:
    vector<Patient> GetList();
    Patient Find(string key);
    void Update(Patient pat);

    bool Delete(string key){
        return 0;
    }
};