#include "SharedBuffer.h"

void SharedBuffer::setData(const std::string &data) {
    buffer_ += data;
    logger_->info("SharedBuffer::setData: " + data);
}

bool SharedBuffer::isEmpty() const {
    logger_->info("SharedBuffer::isEmpty");
    return buffer_.empty();
}

std::string SharedBuffer::getData() {
    std::string data = buffer_;
    buffer_.clear();
    logger_->info("SharedBuffer::getData: " + data);
    return data;
}


