#ifndef PROGRAM1_SHAREDBUFFER_H
#define PROGRAM1_SHAREDBUFFER_H

#include <mutex>
#include <string>

class SharedBuffer {
public:
    SharedBuffer() = default;
    ~SharedBuffer() = default;

    void setData(const std::string &data);
    std::string getData();

private:
    std::string buffer_;
    std::mutex mutex_;
};


#endif //PROGRAM1_SHAREDBUFFER_H
