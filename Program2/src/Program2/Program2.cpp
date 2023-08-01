#include "Program2.h"

void Program2::run() {
    while (true) {
        // obtaining a connection
        int clientSocket = networkConnecter_.acceptConnection();

        if (clientSocket != -1) {
            // receiving data from the program1
            std::string data = networkConnecter_.receiveData(clientSocket);
            networkConnecter_.closeConnection(clientSocket);

            if (data == "exit") {
                logger_->info("Program2::run: " + data);
                std::cout << data << std::endl;
                break;
            }

            // data processing
            try {
                dataProcessor_.process(data);
            } catch (const std::exception &exception) {
                std::cout << "Error while processing data" << std::endl;
                logger_->error("Program2::run: Error while processing data. Exception: " + std::string(exception.what()));
            }
        }
    }
}
