#pragma once
#include "Doctor.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

class ConnectHandler{
private:
    Doctor _doc;
    int sock = 0;
public:
    
    void Connect(){
        struct sockaddr_in serv_addr;
        char buffer[1024] = {0};

        // Создание сокета
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cout << "Ошибка создания сокета" << std::endl;
            return;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Преобразование IPv4 и IPv6 адресов из текстового представления в двоичное
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            std::cout << "Неверный адрес/адрес не поддерживается" << std::endl;
            return;
        }

        // Подключение к серверу
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cout << "Ошибка подключения" << std::endl;
            return;
        }

        std::cout<<"successful connection\n";

        while(true){
            string str;
            std::cout<<"next "<<"update "<<"add drug "<<"add hs\n";
            std::cin>>str;
            if (str == "next" || str == "Next"){
                try{
                    GetPatient();
                }
                catch(const char* error){
                    std::cout<<error<<"\n";
                }
            }
            else if (str == "update" || str == "Update"){
                try{
                    UpdatePatient(_doc.GetPatient());
                }
                catch(const char* error){
                    std::cout<<error<<"\n";
                }
            }
            else if(str == "add hs"){
                string HealthScript;
                std::cout<<"enter Health Script\n";
                std::cin>>HealthScript;
                _doc.AppendHealthScript(HealthScript);
            }
            else if(str == "add drug"){
                string drugs;
                std::cout<<"1) Aspirin 2)Ibuprofen 3)Acetaminophen 4)Amoxicillin 5)Metformin 6)Lisinopril 7)Simvastatin 8)Omeprazole 9)Levothyroxine 10)Atorvastatin\n";
                std::cin>>drugs;
                _doc.AppendDrug(drugs);
            }
            else if (str == "exit" ){
                break;
            }  
            else{
                std::cout<<"command not found\n";
            }
            
        }
        close(sock);
        return;
    }

    void GetPatient(){
        const char* m = "next";
        send(sock, m, strlen(m), 0);
        char buffer[1024] = {0};
        while (true){
            int len = read(sock, buffer, 1024);
            if (len > 0){
                if (buffer[0] !=  '0'){
                    throw buffer;
                }
                string pat1(buffer);
                string pat2 = pat1.substr(1, pat1.size() - 1);
                Patient patient(pat2);
                _doc.SetPatient(patient);
                return;
            }
        }
    }

    void UpdatePatient(Patient pat){
        string str = pat.Tostr();
        str = "update" + str;
        const char* message = str.c_str();
        send(sock, message, strlen(message), 0);
        char* buffer;
        int len = read(sock, buffer, 1024);
        if (!strcmp(buffer, "ok")){
            return;
        }
        throw "failed update";
    }
};