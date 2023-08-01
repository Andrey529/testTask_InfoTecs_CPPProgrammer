#include "Program1.h"

void Program1::run() {
    std::thread inputThread(&Program1::inputThreadFunction, this);
    std::thread sendingThread(&Program1::sendingThreadFunction, this);

    inputThread.join();
    sendingThread.join();
}

void Program1::inputThreadFunction() {
    while (true) {
        try {
            // user input
            std::string input;
            std::cout << "Input string: ";
            std::cin >> input;

            DataProcessor dataProcessor;

            if (input == "exit") {
                std::unique_lock<std::mutex> uniqueLock(mutex_);
                // paste the exit status into the synchronized buffer
                sharedBuffer_.setData(input);
                uniqueLock.unlock();
                cv_.notify_one();
                logger_->info("Program1::inputThreadFunction: " + input);
                break;
            }
                // check that the entered string consists only of digits
                // and that its length does not exceed 64
            else if (dataProcessor.isValid(input)) {
                logger_->info("Program1::inputThreadFunction: Input string: " + input);

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
        } catch (const std::exception &exception) {
            std::cout << "Error while processing data in inputThreadFunction" << std::endl;
            logger_->error("Program1::inputThreadFunction: Error while processing data in inputThreadFunction");
        }
    }
}

void Program1::sendingThreadFunction() {
    while (true) {
        try {
            // get data from buffer
            std::unique_lock<std::mutex> uniqueLock(mutex_);
            cv_.wait(uniqueLock, [&]() { return !sharedBuffer_.isEmpty(); });
            std::string data = sharedBuffer_.getData();
            uniqueLock.unlock();

            // output of received data from the buffer to the screen
            std::cout << "\nBuffered data: " << data << std::endl;
            logger_->info("Program1::sendingThreadFunction: Buffered data: " + data);

            if (data == "exit") {
                // sending exit status to a program2
                NetworkConnecter networkConnecter(program2Ip_, program2Port_);
                networkConnecter.sendData(data);
                logger_->info("Program1::sendingThreadFunction: " + data);
                break;
            } else {
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
        } catch (const std::exception &exception) {
            std::cout << "Error while processing data in sendingThreadFunction" << std::endl;
            logger_->error("Program1::sendingThreadFunction: Error while processing data in sendingThreadFunction");
        }
    }
}
