#include "DataProcessor.h"

void DataProcessor::sortDescending(std::string &data) {
    std::sort(data.begin(), data.end(), std::greater<char>());
    logger_->info("DataProcessor::sortDescending: Sorted data = " + data);
}

void DataProcessor::replaceEvenNumbers(std::string &data) {
    // replace all even digits with "KB" characters
    std::string copy;
    for (auto &ch : data) {
        if (std::isdigit(ch) && (ch - '0') % 2 == 0) {
            copy += "KB";
        } else {
            copy += ch;
        }
    }
    data = copy;
    logger_->info("DataProcessor::replaceEvenNumbers: Replaced even numbers = " + data);
}

void DataProcessor::processData(std::string &data) {
    sortDescending(data);

    replaceEvenNumbers(data);
}

bool DataProcessor::isValid(const std::string &data) {
    // check that string size not greater than 64
    if (data.size() > 64) {
        logger_->info("DataProcessor::isValid: Data is invalid = " + data);
        return false;
    }

    // check that the whole string consists only of digits
    for (const auto &ch : data) {
        if (!std::isdigit(ch)) {
            logger_->info("DataProcessor::isValid: Data is invalid = " + data);
            return false;
        }
    }

    logger_->info("DataProcessor::isValid: Data is valid = " + data);
    return true;
}
