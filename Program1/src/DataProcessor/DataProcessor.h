#ifndef PROGRAM1_DATAPROCESSOR_H
#define PROGRAM1_DATAPROCESSOR_H


#include <string>
#include "Logger/Loggable.h"

class DataProcessor : public Loggable {
public:
    bool isValid(const std::string &data);
    void processData(std::string &data);
private:
    void sortDescending(std::string &data);
    void replaceEvenNumbers(std::string &data);
};


#endif //PROGRAM1_DATAPROCESSOR_H
