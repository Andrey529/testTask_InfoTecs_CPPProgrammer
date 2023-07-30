#ifndef PROGRAM1_SHAREDBUFFER_H
#define PROGRAM1_SHAREDBUFFER_H


#include <string>

class SharedBuffer {
public:
    SharedBuffer() = default;
    ~SharedBuffer() = default;

    void setData(const std::string &data);
    std::string getData();
    bool isEmpty() const;
private:
    std::string buffer_;
};


#endif //PROGRAM1_SHAREDBUFFER_H
