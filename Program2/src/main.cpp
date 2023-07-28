#include "Program2/Program2.h"

int main() {
    std::string ipAddress = "127.0.0.1";
    int port = 12345;
    Program2 program2(ipAddress, port);
    program2.run();
    return 0;
}
