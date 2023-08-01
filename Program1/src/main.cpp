#include "Program1/Program1.h"

int main() {
    Logger::Init("../logs/log.txt");
    std::string program2Ip = "127.0.0.1";
    int program2Port = 12345;
    Program1 program1(program2Ip, program2Port);
    program1.run();
    return 0;
}