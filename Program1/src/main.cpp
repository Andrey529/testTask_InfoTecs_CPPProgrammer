#include <iostream>
#include <thread>
#include "SharedBuffer/SharedBuffer.h"

void readData(SharedBuffer &sharedBuffer) {
    std::string data = sharedBuffer.getData();
    std::cout << data << std::endl;
}

void writeData(SharedBuffer &sharedBuffer) {
    std::string data = "123";
    sharedBuffer.setData(data);
}

int main() {
    SharedBuffer sharedBuffer;
    std::thread t1(writeData, std::ref(sharedBuffer));
    std::thread t2(readData, std::ref(sharedBuffer));

    t1.join();
    t2.join();

}