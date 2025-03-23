#include "ConnectionHandler.h"

void ConnectionHandler::Connect(){
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Ошибка при создании сокета");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Ошибка установки опций сокета");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Ошибка привязки");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Ошибка при прослушивании");
        exit(EXIT_FAILURE);
    }

    std::cout << "Ожидание подключения клиента..." << std::endl;

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Ошибка при принятии соединения");
        exit(EXIT_FAILURE);
    }

    std::cout << "Клиент подключен!" << std::endl;

    ReqHandler();

}

void ConnectionHandler::ReqHandler(){
    while(true){
        char buffer[1024] = {0};
        int len = read(new_socket, buffer, 1024);
        if (len > 0){   
            if (!strcmp(buffer, "next")){
                try{
                    sendPatient();
                }
                catch(const char* error){
                    send(new_socket, error, strlen(error), 0);
                }
            }
            else if (strstr(buffer, "update") != nullptr){
                string str(buffer);
                updateReq(str);
            }
            else{
                std::cout<<"command not found\n";
            }
        }
    }
}

void ConnectionHandler::sendPatient(){
    try{
        Patient pat = _patContr.Next();
        string str = "0" + pat.Tostr();
        const char* messege = str.c_str();
        send(new_socket, messege, strlen(messege), 0);
    }
    catch(const char* error){
        throw error;
    }
}

void ConnectionHandler::updateReq(string pat){
    std::cout<<"requare\n";
    string str = pat.substr(6, pat.size() - 6);
    Patient patient(str);
    _patContr.UpdatePatient(patient);
}