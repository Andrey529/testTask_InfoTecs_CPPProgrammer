#include "DataProcessor.h"

void DataProcessor::process(const std::string &data) {
    if (data.size() > 2 && std::stoi(data) % 32 == 0) {
        std::cout << "Сorrect data have been received: " << data << std::endl;
    } else {
        std::cout << "Error - Incorrect data received: " << data << std::endl;
    }
}
