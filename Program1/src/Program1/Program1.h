#ifndef PROGRAM1_PROGRAM1_H
#define PROGRAM1_PROGRAM1_H


#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>

#include "../DataProcessor/DataProcessor.h"
#include "../SharedBuffer/SharedBuffer.h"
#include "../NetworkConnecter/NetworkConnecter.h"
#include "Logger/Loggable.h"

class Program1 : public Loggable {
public:
    Program1(const std::string &program2Ip, const int &program2Port)
            : program2Ip_(program2Ip), program2Port_(program2Port), sharedBuffer_(), mutex_(), cv_() {}

    void run();

private:
    void inputThreadFunction();

    void sendingThreadFunction();

    std::string program2Ip_;
    int program2Port_;
    SharedBuffer sharedBuffer_;
    std::mutex mutex_;
    std::condition_variable cv_;
};


#endif //PROGRAM1_PROGRAM1_H
