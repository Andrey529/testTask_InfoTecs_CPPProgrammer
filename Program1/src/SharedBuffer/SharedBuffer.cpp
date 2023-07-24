#include "SharedBuffer.h"

void SharedBuffer::setData(const std::string &data) {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    buffer_ += data;
}

std::string SharedBuffer::getData() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    std::string data = buffer_;
    buffer_.clear();
    return data;
}


