#include "Program2.h"

void Program2::run() {
    while (true) {
        int clientSocket = networkConnecter_.acceptConnection();

        if (clientSocket != -1) {
            std::string data = networkConnecter_.receiveData(clientSocket);
            networkConnecter_.closeConnection(clientSocket);

            // TODO() : process data
        }
    }
}
