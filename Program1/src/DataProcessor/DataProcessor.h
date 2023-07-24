#ifndef PROGRAM1_DATAPROCESSOR_H
#define PROGRAM1_DATAPROCESSOR_H

#include <string>

class DataProcessor {
public:
    void processData(std::string &data) {

        sortDescending(data);

        replaceEvenNumbers(data);
    }

private:

    void sortDescending(std::string &data) {
        std::sort(data.begin(), data.end(), std::greater<char>());
    }

    void replaceEvenNumbers(std::string &data) {
        std::string copy;
        for (char &ch : data) {
            if (std::isdigit(ch) && (ch - '0') % 2 == 0) {
                copy += "KB";
            } else {
                copy += ch;
            }
        }
        data = copy;
    }
};


#endif //PROGRAM1_DATAPROCESSOR_H
