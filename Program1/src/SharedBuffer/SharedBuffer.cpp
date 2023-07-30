#include "SharedBuffer.h"

void SharedBuffer::setData(const std::string &data) {
    buffer_ += data;
}

bool SharedBuffer::isEmpty() const {
    return buffer_.empty();
}

std::string SharedBuffer::getData() {
    std::string data = buffer_;
    buffer_.clear();
    return data;
}


