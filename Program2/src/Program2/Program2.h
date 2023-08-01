#ifndef PROGRAM2_PROGRAM2_H
#define PROGRAM2_PROGRAM2_H


#include "../NetworkConnecter/NetworkConnecter.h"
#include "../DataProcessor/DataProcessor.h"
#include "Logger/Loggable.h"

class Program2 : public Loggable {
public:
    Program2(const std::string &ipAddress, const int port) : networkConnecter_(ipAddress, port),
                                                                         dataProcessor_() {}

    ~Program2() = default;

    void run();

private:
    NetworkConnecter networkConnecter_;
    DataProcessor dataProcessor_;
};


#endif //PROGRAM2_PROGRAM2_H
