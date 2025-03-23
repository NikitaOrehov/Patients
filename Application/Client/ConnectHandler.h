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
    int sock = 0;
public:
    
    void Connect(){
        struct sockaddr_in serv_addr;
        char buffer[1024] = {0};

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cout << "Ошибка создания сокета" << std::endl;
            return;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            std::cout << "Неверный адрес/адрес не поддерживается" << std::endl;
            return;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cout << "Ошибка подключения" << std::endl;
            return;
        }

        std::cout<<"successful connection\n";
    }

    void Disconnect(){
        close(sock);
        return;
    }

    Patient GetPatient(){
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
                return patient;
            }
        }
    }

    void UpdatePatient(Patient pat){
        string str = pat.Tostr();
        str = "update" + str;
        const char* message = str.c_str();
        send(sock, message, strlen(message), 0);
    }
};