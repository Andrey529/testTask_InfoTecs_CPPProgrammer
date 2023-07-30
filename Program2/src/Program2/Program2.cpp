#include "Program2.h"

void Program2::run() {
    while (true) {
        // obtaining a connection
        int clientSocket = networkConnecter_.acceptConnection();

        if (clientSocket != -1) {
            // receiving data from the program1
            std::string data = networkConnecter_.receiveData(clientSocket);
            networkConnecter_.closeConnection(clientSocket);

            // data processing
            dataProcessor_.process(data);
        }
    }
}
