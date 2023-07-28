#include "NetworkConnecter.h"

NetworkConnecter::NetworkConnecter(const std::string &serverIpAddress, const int serverPort)
        : serverIpAddress_(serverIpAddress), serverPort_(serverPort) {

    if (serverPort_ < 1024 || serverPort_ > 65535) {
        std::cerr << "Invalid port number. Port must be in [1024; 65535]" << std::endl;
        exit(1);
    }

    int status;
    struct addrinfo hints = {};
    struct addrinfo *servinfo;

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(serverIpAddress_.c_str(), std::to_string(serverPort_).c_str(), &hints, &servinfo);

    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        exit(1);
    }

    std::cout << "Ip address = " << serverIpAddress_ << " , port = " << serverPort_ << std::endl;

    for (auto p = servinfo; p != nullptr; p = p->ai_next) {

        serverSocket_ = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (serverSocket_ == -1) {
            std::cerr << "Server socket error: continue. Error number = " << errno << std::endl;
            continue;
        }

        int yes = 1;
        if (setsockopt(serverSocket_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            std::cerr << "Error: setsockopt" << std::endl;
            exit(1);
        }

        status = bind(serverSocket_, p->ai_addr, p->ai_addrlen);
        if (status == -1) {
            std::cerr << "Server bind error: continue. Error number = " << errno << std::endl;
            continue;
        }

        break;
    }

    if (servinfo == nullptr) {
        std::cerr << "Server failed to bind" << std::endl;
        close(serverSocket_);
        exit(1);
    }

    freeaddrinfo(servinfo);

    status = listen(serverSocket_, 20);
    if (status == -1) {
        std::cerr << "Error listen" << std::endl;
        close(serverSocket_);
        exit(1);
    }
}

NetworkConnecter::~NetworkConnecter() {
    close(serverSocket_);
}

int NetworkConnecter::acceptConnection() {
    struct sockaddr_storage their_address{};
    socklen_t sin_size;

    sin_size = sizeof(their_address);
    int clientSocket = accept(serverSocket_, (struct sockaddr *) &their_address, &sin_size);
    if (clientSocket == -1) {
        std::cerr << "Accept error, continue" << std::endl;
        return -1;
    }

    return clientSocket;
}

std::string NetworkConnecter::receiveData(int clientSocket) {
    char buffer[bufferSize_] = {};
    ssize_t bytesReceived = read(clientSocket, buffer, bufferSize_);
    if (bytesReceived <= 0) {
        std::cerr << "Failed to read bytes from client socket connection" << std::endl;
        return "";
    }

    buffer[bytesReceived] = '\0';
    std::string dataReceived(buffer);
    return dataReceived;
}

void NetworkConnecter::closeConnection(int socket) {
    close(socket);
}
