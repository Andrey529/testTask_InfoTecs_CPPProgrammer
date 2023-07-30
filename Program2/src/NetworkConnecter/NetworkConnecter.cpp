#include "NetworkConnecter.h"

NetworkConnecter::NetworkConnecter(const std::string &ipAddress, const int &port)
        : ipAddress_(ipAddress), port_(port) {

    if (port_ < 1024 || port_ > 65535) {
        std::cerr << "Invalid port number. Port must be in [1024; 65535]" << std::endl;
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
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        exit(1);
    }

    std::cout << "Ip address = " << ipAddress_ << " , port = " << port_ << std::endl;

    for (p = servinfo; p != nullptr; p = p->ai_next) {

        socket_ = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_ == -1) {
            std::cerr << "Program2 socket error: continue. Error number = " << errno << std::endl;
            continue;
        }

        int yes = 1;
        if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            std::cerr << "Program2 Error: setsockopt" << std::endl;
            exit(1);
        }

        status = bind(socket_, p->ai_addr, p->ai_addrlen);
        if (status == -1) {
            std::cerr << "Program2 bind error: continue. Error number = " << errno << std::endl;
            continue;
        }

        break;
    }

    if (p == nullptr) {
        std::cerr << "Program2 failed to bind" << std::endl;
        close(socket_);
        exit(1);
    }

    freeaddrinfo(servinfo);

    status = listen(socket_, 20);
    if (status == -1) {
        std::cerr << "Error listen" << std::endl;
        close(socket_);
        exit(1);
    }
}

NetworkConnecter::~NetworkConnecter() {
    close(socket_);
}

int NetworkConnecter::acceptConnection() {
    struct sockaddr_storage their_address{};
    socklen_t sin_size;

    sin_size = sizeof(their_address);
    int clientSocket = accept(socket_, (struct sockaddr *) &their_address, &sin_size);
    if (clientSocket == -1) {
        std::cerr << "Accept error, continue" << std::endl;
        return -1;
    }

    return clientSocket;
}

std::string NetworkConnecter::receiveData(int clientSocket) {
    char buffer[bufferSize_] = {};
    ssize_t bytesReceived = recv(clientSocket, buffer, bufferSize_, 0);
    if (bytesReceived <= 0) {
        std::cerr << "Failed to read bytes from program1 socket connection" << std::endl;
        return "";
    }

    buffer[bytesReceived] = '\0';
    std::string dataReceived(buffer);
    return dataReceived;
}

void NetworkConnecter::closeConnection(int socket) {
    close(socket);
}
