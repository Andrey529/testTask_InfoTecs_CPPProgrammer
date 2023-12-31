#ifndef PROGRAM2_NETWORKCONNECTER_H
#define PROGRAM2_NETWORKCONNECTER_H


#include <string>
#include <iostream>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "Logger/Loggable.h"

class NetworkConnecter : public Loggable {
public:
    NetworkConnecter(const std::string &ipAddress, const int &port);

    ~NetworkConnecter();

    int acceptConnection();

    std::string receiveData(int clientSocket);

    void closeConnection(int socket);

private:
    std::string ipAddress_;
    int port_;
    int socket_;
    static const int bufferSize_ = 1024;
};


#endif //PROGRAM2_NETWORKCONNECTER_H
