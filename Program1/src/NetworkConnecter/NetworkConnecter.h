#ifndef PROGRAM1_NETWORKCONNECTER_H
#define PROGRAM1_NETWORKCONNECTER_H


#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>

#include <chrono>
#include <thread>

class NetworkConnecter {
public:
    NetworkConnecter(const std::string &serverIp, const int &serverPort);

    ~NetworkConnecter();

    void sendData(const std::string &data);

private:
    bool connectToServer();

    void *get_in_addr(struct sockaddr *sa);

    int socketFileDescriptor_;
    std::string program2Ip_;
    int program2Port_;
};


#endif //PROGRAM1_NETWORKCONNECTER_H
