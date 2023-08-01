#include "NetworkConnecter.h"

NetworkConnecter::NetworkConnecter(const std::string &ipAddress, const int &port)
        : ipAddress_(ipAddress), port_(port) {

    if (port_ < 1024 || port_ > 65535) {
        logger_->error("NetworkConnecter::NetworkConnecter: Invalid port number. Port must be in [1024; 65535]");
        exit(1);
    }

    int status;
    struct addrinfo hints = {};
    struct addrinfo *servinfo, *p;

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(ipAddress_.c_str(), std::to_string(port_).c_str(), &hints, &servinfo);

    if (status != 0) {
        logger_->error("NetworkConnecter::NetworkConnecter: getaddrinfo error: " + std::string(gai_strerror(status)));
        exit(1);
    }

    logger_->info("NetworkConnecter::NetworkConnecter: Ip address = " + ipAddress_ + " , port = " + std::to_string(port_));

    for (p = servinfo; p != nullptr; p = p->ai_next) {

        socket_ = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_ == -1) {
            logger_->error("NetworkConnecter::NetworkConnecter: Program2 socket error continue. Error number = " + std::to_string(errno));
            continue;
        }

        int yes = 1;
        if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            logger_->error("NetworkConnecter::NetworkConnecter: Program2 error setsockopt");
            exit(1);
        }

        status = bind(socket_, p->ai_addr, p->ai_addrlen);
        if (status == -1) {
            logger_->error("NetworkConnecter::NetworkConnecter: Program2 bind error - continue. Error number = " + std::to_string(errno));
            continue;
        }

        break;
    }

    if (p == nullptr) {
        logger_->error("NetworkConnecter::NetworkConnecter: Program2 failed to bind");
        close(socket_);
        exit(1);
    }

    freeaddrinfo(servinfo);

    status = listen(socket_, 20);
    if (status == -1) {
        logger_->error("NetworkConnecter::NetworkConnecter: Error listen");
        close(socket_);
        exit(1);
    }

    logger_->info("NetworkConnecter::NetworkConnecter: Success");
}

NetworkConnecter::~NetworkConnecter() {
    logger_->info("NetworkConnecter::~NetworkConnecter");
    close(socket_);
}

int NetworkConnecter::acceptConnection() {
    struct sockaddr_storage their_address{};
    socklen_t sin_size;

    sin_size = sizeof(their_address);
    int clientSocket = accept(socket_, (struct sockaddr *) &their_address, &sin_size);
    if (clientSocket == -1) {
        logger_->error("NetworkConnecter::acceptConnection: Accept error");
        return -1;
    }

    logger_->info("NetworkConnecter::acceptConnection: Accepted new connection");
    return clientSocket;
}

std::string NetworkConnecter::receiveData(int clientSocket) {
    char buffer[bufferSize_] = {};
    ssize_t bytesReceived = recv(clientSocket, buffer, bufferSize_, 0);
    if (bytesReceived <= 0) {
        logger_->error("NetworkConnecter::receiveData: Failed to read bytes from program1 socket connection");
        return "";
    }

    buffer[bytesReceived] = '\0';
    std::string dataReceived(buffer);
    logger_->info("NetworkConnecter::receiveData: Received new data = " + dataReceived);
    return dataReceived;
}

void NetworkConnecter::closeConnection(int socket) {
    logger_->info("NetworkConnecter::closeConnection");
    close(socket);
}
