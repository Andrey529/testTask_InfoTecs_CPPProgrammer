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
    close(socketFileDescriptor_);
}

void NetworkConnecter::sendData(const std::string &data) {
    // TODO: обработать случай, когда посылается слишком большой объем данных, который не влазит в 1 посылку

    int bytesSent = send(socketFileDescriptor_, data.c_str(), data.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Error sending data to program2" << std::endl;
        if (errno == ECONNRESET || errno == ENOTCONN || errno == EPIPE) {
            while (true) {
                std::cout << "Try to connect to program2" << std::endl;
                close(socketFileDescriptor_);
                if (connectToServer()) {
                    break;
                }
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            sendData(data);
        }
    }
}

bool NetworkConnecter::connectToServer() {
    int status;
    struct addrinfo hints = {}, *servinfo, *p;

    std::memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(program2Ip_.c_str(), std::to_string(program2Port_).c_str(), &hints, &servinfo);

    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return false;
    }

    for (p = servinfo; p != nullptr; p = p->ai_next) {
        socketFileDescriptor_ = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socketFileDescriptor_ == -1) {
            std::cerr << "Program1 error: socket to program2" << std::endl;
            continue;
        }

        status = connect(socketFileDescriptor_, p->ai_addr, p->ai_addrlen);
        if (status == -1) {
            close(socketFileDescriptor_);
            std::cerr << "Program1 error: connect to program2" << std::endl;
            continue;
        }
        break;
    }
    if (p == nullptr) {
        std::cerr << "Program1 error: failed to connect to program2" << std::endl;
        return false;
    }

    char s[INET6_ADDRSTRLEN];
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), s, sizeof s);
//    std::cout << "Program1: connecting to " << s << std::endl;

    freeaddrinfo(servinfo);
    return true;
}

void *NetworkConnecter::get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}
