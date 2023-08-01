#ifndef PROGRAM1_SHAREDBUFFER_H
#define PROGRAM1_SHAREDBUFFER_H


#include <string>
#include "Logger/Loggable.h"

class SharedBuffer : public Loggable {
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
