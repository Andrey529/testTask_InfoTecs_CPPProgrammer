#include "NetworkConnecter.h"

NetworkConnecter::NetworkConnecter(const std::string &serverIp, const int &serverPort)
        : socketFileDescriptor_(), program2Ip_(serverIp), program2Port_(serverPort) {
    while (true) {
        if (connectToServer()) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

NetworkConnecter::~NetworkConnecter() {
    logger_->info("NetworkConnecter::~NetworkConnecter: Close connection");
    close(socketFileDescriptor_);
}

void NetworkConnecter::sendData(const std::string &data) {
    int bytesSent = send(socketFileDescriptor_, data.c_str(), data.size(), 0);
    if (bytesSent == -1) {
        logger_->error("NetworkConnecter::sendData: Error sending data to program2: Data = " + data);
        if (errno == ECONNRESET || errno == ENOTCONN || errno == EPIPE) {
            while (true) {
                std::cout << "Try to connect to program2" << std::endl;
                logger_->info("NetworkConnecter::sendData: Try to connect to program2");
                close(socketFileDescriptor_);
                if (connectToServer()) {
                    break;
                }
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            sendData(data);
        }
    }
    logger_->info("NetworkConnecter::sendData: Sent data to program2. Data = " + data);
}

bool NetworkConnecter::connectToServer() {
    int status;
    struct addrinfo hints = {}, *servinfo, *p;

    std::memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(program2Ip_.c_str(), std::to_string(program2Port_).c_str(), &hints, &servinfo);

    if (status != 0) {
        logger_->error("NetworkConnecter::connectToServer: getaddrinfo error: " + std::string(gai_strerror(status)));
        return false;
    }

    for (p = servinfo; p != nullptr; p = p->ai_next) {
        socketFileDescriptor_ = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socketFileDescriptor_ == -1) {
            logger_->error("NetworkConnecter::connectToServer: Error socket to program2");
            continue;
        }

        status = connect(socketFileDescriptor_, p->ai_addr, p->ai_addrlen);
        if (status == -1) {
            close(socketFileDescriptor_);
            logger_->error("NetworkConnecter::connectToServer: Error connect to program2");
            continue;
        }
        break;
    }
    if (p == nullptr) {
        logger_->error("NetworkConnecter::connectToServer: Failed to connect to program2");
        return false;
    }

    char s[INET6_ADDRSTRLEN];
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), s, sizeof s);
    logger_->info("NetworkConnecter::connectToServer: Program1 connecting to " + std::string(s));

    freeaddrinfo(servinfo);
    return true;
}

void *NetworkConnecter::get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}
