#include <libpq-fe.h>
#include "DataBaseWorker.h"
#include <iostream>
#include <cstring>

Patient DataBaseWorker::Find(string key){
    const char *conninfo = "dbname=patients user=postgres password=1379 host=localhost port=5432";

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        PQfinish(conn);
        throw "Connection to database failed: ";
    }
    else std::cout << "Connected to database successfully!" << std::endl;

    string str = "SELECT * FROM PATIENTS WHERE id = " + key;
    const char* require = str.c_str();
    PGresult* patient = PQexec(conn, require);

    str = "SELECT * FROM VISIT WHERE id_patient = " + key;
    require = str.c_str();
    PGresult* visits = PQexec(conn, require);



    if (PQresultStatus(patient) != PGRES_TUPLES_OK || PQresultStatus(visits) != PGRES_TUPLES_OK) {
        PQfinish(conn);
        throw "Query failed";
    } else {
        int rows_patients = PQntuples(patient);
        if (rows_patients > 0) {
            int id = std::stoi(PQgetvalue(patient, 0, 0));
            string surname(PQgetvalue(patient, 0, 1));
            string name(PQgetvalue(patient, 0, 2));
            string patron(PQgetvalue(patient, 0, 3));
            Gender g;
            if (!strcmp(PQgetvalue(patient, 0, 4), "Man")) g = man; 
            else g = woman;
            Patient p(id, surname, name, patron, g);

            int row_visit = PQntuples(visits);
            for (int i = 0; i < row_visit; i++){
                string anamnes(PQgetvalue(visits, i, 1));
                string ms(PQgetvalue(visits, i, 2));
                vector<string> drugs;
                string drugsStr(PQgetvalue(visits, i, 3));
                string drugInt;
                for(int j = 0; j < drugsStr.size(); j++){
                    if (drugsStr[j] == 32){
                        str = "SELECT drugs FROM drugs WHERE id = " + drugInt;
                        require = str.c_str();
                        PGresult* drug = PQexec(conn, require);
                        if (PQresultStatus(drug) != PGRES_TUPLES_OK){
                            throw "no found drug";
                        }
                        drugs.push_back(string(PQgetvalue(drug, 0, 0)));
                        drugInt.clear();
                    }
                    drugInt += drugsStr[j];
                }


                str = "SELECT drugs FROM drugs WHERE id = " + drugInt;
                require = str.c_str();
                PGresult* drug = PQexec(conn, require);
                if (PQresultStatus(drug) != PGRES_TUPLES_OK){
                    "no found drug";
                    }
                drugs.push_back(string(PQgetvalue(drug, 0, 0)));

                Visit vis;
                vis.anamn = anamnes;
                vis.ms = ms;
                vis.drugs = drugs;
                p.AddVisit(vis);             
            }
            PQfinish(conn);
            return p;

        } else {
            PQfinish(conn);
            throw "No rows found with id = " + key;
        }
    }
}

vector<Patient> DataBaseWorker::GetList(){
    vector<Patient> patietns;

    const char *conninfo = "dbname=patients user=postgres password=1379 host=localhost port=5432";
    PGconn* conn = PQconnectdb(conninfo);
    
    if (PQstatus(conn) != CONNECTION_OK) {
        PQfinish(conn);
        throw "Connection to database failed";
    }
    else std::cout << "Connected to database successfully!" << std::endl;

    const char* require = "SELECT * FROM PATIENTS;";
    PGresult* res = PQexec(conn, require);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQfinish(conn);
        throw "incorrect require";
    }
    else{
        int row = PQntuples(res);
        if (row > 0){
            for (int i = 0; i < row; i++){
                int id = std::stoi(PQgetvalue(res, i, 0));
                string surname(PQgetvalue(res, i, 1));
                string name(PQgetvalue(res, i, 2));
                string patron(PQgetvalue(res, i, 3));
                Gender g;
                if (!strcmp("Man", PQgetvalue(res, i, 4))) g = man; 
                else g = woman;
                Patient p(id, surname, name, patron, g);

                string str = "SELECT * FROM VISIT WHERE id_patient = " + to_string(id);
                require = str.c_str();
                PGresult* visits = PQexec(conn, require);

                int row_visit = PQntuples(visits);
                for (int j = 0; j < row_visit; j++){
                    Visit vis;
                    vis.anamn = string(PQgetvalue(visits, j, 1));
                    vis.ms = string(PQgetvalue(visits, j, 2));
                    string drugsStr(PQgetvalue(visits, j, 3));
                    string drugInt;
                    for(int k = 0; k < drugsStr.size(); k++){
                        if (drugsStr[k] == 32){
                            str = "SELECT drugs FROM drugs WHERE id = " + drugInt;
                            require = str.c_str();
                            PGresult* drug = PQexec(conn, require);
                            if (PQresultStatus(drug) != PGRES_TUPLES_OK){
                                throw "no found drug";
                            }
                            vis.drugs.push_back(string(PQgetvalue(drug, 0, 0)));
                            drugInt.clear();
                        }
                        drugInt += drugsStr[k];
                    }  

                    str = "SELECT drugs FROM drugs WHERE id = " + drugInt;
                    require = str.c_str();
                    PGresult* drug = PQexec(conn, require);
                    if (PQresultStatus(drug) != PGRES_TUPLES_OK){
                        "no found drug";
                        }
                    vis.drugs.push_back(string(PQgetvalue(drug, 0, 0)));
                    p.AddVisit(vis);
                }
                patietns.push_back(p);
            }
        }
        else {
            PQfinish(conn);
            throw "table is empty";
        }
    }

    return patietns;
}


void DataBaseWorker::Update(Patient pat){
    const char *conninfo = "dbname=patients user=postgres password=1379 host=localhost port=5432";
    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        PQfinish(conn);
        throw "Connection to database failed: ";
    }
    else std::cout << "Connected to database successfully!" << std::endl;

    string str;
    Visit vis = pat.pop_back();
    vector<string> drugs = vis.drugs;
    string strDrugs;
    for (int i = 0; i < drugs.size(); i++){
        str.clear();
        str = "SELECT id FROM DRUGS WHERE drugs = \'" + drugs[i] + "\';";
        const char* require = str.c_str();
        PGresult* res = PQexec(conn, require);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            PQfinish(conn);
            throw "drugs not found in table";
        }
        if (PQntuples(res) > 0){
            strDrugs = strDrugs + PQgetvalue(res, 0, 0) + " ";
        }
    }
    if (strDrugs.size() > 0){
        strDrugs.pop_back();
    }
    str = "INSERT INTO VISIT (anomnes, ms, id_drugs, id_patient) VALUES ";
    string strValue = "(\'" + vis.anamn + "\', \'" + vis.ms + "\', \'" + strDrugs + "\'," + pat.Tostr()[0] + ");";
    str += strValue;
    const char* require = str.c_str();
    PGresult* res = PQexec(conn, require);
}