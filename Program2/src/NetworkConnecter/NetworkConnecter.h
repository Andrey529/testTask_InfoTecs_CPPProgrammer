#ifndef PROGRAM2_NETWORKCONNECTER_H
#define PROGRAM2_NETWORKCONNECTER_H


#include <string>
#include <iostream>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class NetworkConnecter {
public:
    NetworkConnecter(const std::string &serverIpAddress, const int serverPort);

    ~NetworkConnecter();

    int acceptConnection();

    std::string receiveData(int clientSocket);

    void closeConnection(int socket);

private:
    std::string serverIpAddress_;
    int serverPort_;
    int serverSocket_;
    static const int bufferSize_ = 1024;
};


#endif //PROGRAM2_NETWORKCONNECTER_H
