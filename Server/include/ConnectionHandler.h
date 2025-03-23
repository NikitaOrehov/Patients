#pragma once
#include "PatientController.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080



class ConnectionHandler{
private:
    PatientController _patContr;  
    int server_fd, new_socket = 0;
public:
    void Connect();

    void ReqHandler();

    void sendPatient();

    void updateReq(string pat);
};