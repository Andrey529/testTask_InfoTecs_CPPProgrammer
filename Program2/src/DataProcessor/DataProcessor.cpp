#include "DataProcessor.h"

void DataProcessor::process(const std::string &data) {
    if (data.size() > 2 && data.size() % 32 == 0) {
        std::cout << "Сorrect data have been received: " << data << std::endl;
    } else {
        std::cout << "Error - Incorrect data received: " << data << std::endl;
    }
}
