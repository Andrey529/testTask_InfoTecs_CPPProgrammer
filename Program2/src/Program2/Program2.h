#ifndef PROGRAM2_PROGRAM2_H
#define PROGRAM2_PROGRAM2_H


#include "../NetworkConnecter/NetworkConnecter.h"
#include "../DataProcessor/DataProcessor.h"

class Program2 {
public:
    Program2(const std::string &serverIpAddress, const int serverPort) : networkConnecter_(serverIpAddress, serverPort),
                                                                         dataProcessor_() {}

    ~Program2() = default;

    void run();

private:
    NetworkConnecter networkConnecter_;
    DataProcessor dataProcessor_;
};


#endif //PROGRAM2_PROGRAM2_H
