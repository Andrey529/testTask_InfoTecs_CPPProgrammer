#include "Program1.h"

void Program1::run() {
    std::thread inputThread(&Program1::inputThreadFunction, this);
    std::thread sendingThread(&Program1::sendingThreadFunction, this);

    inputThread.join();
    sendingThread.join();
}

void Program1::inputThreadFunction() {
    while (true) {
        // user input
        std::string input;
        std::cout << "Input string: ";
        std::cin >> input;

        // check that the entered string consists only of digits
        // and that its length does not exceed 64
        DataProcessor dataProcessor;
        if (dataProcessor.isValid(input)) {
            // sort the string in descending order
            // and replace all even digits with "KB" characters
            dataProcessor.processData(input);

            std::unique_lock<std::mutex> uniqueLock(mutex_);
            // paste the entered string into the synchronized buffer
            sharedBuffer_.setData(input);
            uniqueLock.unlock();
            cv_.notify_one();

        } else {
            std::cout << "Error: incorrect data entered!" << std::endl;
        }
    }
}

void Program1::sendingThreadFunction() {
    while (true) {
        // get data from buffer
        std::unique_lock<std::mutex> uniqueLock(mutex_);
        cv_.wait(uniqueLock, [&]() { return !sharedBuffer_.isEmpty(); });
        std::string data = sharedBuffer_.getData();
        uniqueLock.unlock();

        // output of received data from the buffer to the screen
        std::cout << "\nBuffered data: " << data << std::endl;

        // calculation the total sum of all elements that are numeric values
        int sum = 0;
        for (const auto &ch: data) {
            if (std::isdigit(ch)) {
                sum += ch - '0';
            }
        }

        // sending data to a program2
        NetworkConnecter networkConnecter(program2Ip_, program2Port_);
        networkConnecter.sendData(std::to_string(sum));
    }
}
