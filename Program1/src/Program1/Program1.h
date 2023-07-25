#ifndef PROGRAM1_PROGRAM1_H
#define PROGRAM1_PROGRAM1_H

#include <iostream>
#include <string>
#include <thread>
#include "../DataProcessor/DataProcessor.h"
#include "../SharedBuffer/SharedBuffer.h"

class Program1 {
public:
    Program1() : dataProcessor_(), sharedBuffer_() {}

    void run() {
        std::thread inputThread(&Program1::inputThreadFunction, this);
        std::thread sendingThread(&Program1::sendingThreadFunction, this);

        inputThread.join();
    }

private:
    void inputThreadFunction() {
        while (true) {
            // user input
            std::string input;
            std::cout << "Input string: ";
            std::cin >> input;

            // check that the entered string consists only of digits
            // and that its length does not exceed 64
            if (dataProcessor_.isValid(input)) {
                // sort the string in descending order
                // and replace all even digits with "KB" characters
                dataProcessor_.processData(input);

                // paste the entered string into the synchronized buffer
                sharedBuffer_.setData(input);
            } else {
                std::cout << "Error: incorrect data entered!" << std::endl;
            }
        }
    }

    void sendingThreadFunction() {
        while (true) {
            std::string data = sharedBuffer_.getData();

            // output of received data from the buffer to the screen
            std::cout << "Buffered data: " << data << std::endl;

            // calculation the total sum of all elements that are numeric values
            int sum = 0;
            for (const auto &ch : data) {
                if (std::isdigit(ch)) {
                    sum += ch - '0';
                }
            }

            // TODO(): передать рассчитанную сумму в Программу №2 через сокеты
        }
    }

    DataProcessor dataProcessor_;
    SharedBuffer sharedBuffer_;
};


#endif //PROGRAM1_PROGRAM1_H
