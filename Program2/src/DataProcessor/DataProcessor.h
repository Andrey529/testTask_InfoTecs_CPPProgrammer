#ifndef PROGRAM2_DATAPROCESSOR_H
#define PROGRAM2_DATAPROCESSOR_H


#include <string>
#include <iostream>

#include "Logger/Loggable.h"

class DataProcessor : public Loggable {
public:
    void process(const std::string &data);
};


#endif //PROGRAM2_DATAPROCESSOR_H
