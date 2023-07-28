#ifndef PROGRAM2_PROGRAM2_H
#define PROGRAM2_PROGRAM2_H


#include "../NetworkConnecter/NetworkConnecter.h"

class Program2 {
public:
    Program2(const std::string &serverIpAddress, const int serverPort) : networkConnecter_(serverIpAddress, serverPort) { }

    ~Program2() = default;

    void run();
private:
    NetworkConnecter networkConnecter_;
};


#endif //PROGRAM2_PROGRAM2_H
