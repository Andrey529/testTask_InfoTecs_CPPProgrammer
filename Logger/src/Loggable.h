#ifndef LOGGER_LOGGABLE_H
#define LOGGER_LOGGABLE_H


#include <memory>
#include "spdlog/spdlog.h"
#include "Logger.h"

class Loggable {
public:
    Loggable();

protected:
    std::shared_ptr<spdlog::logger> logger_;
};


#endif //LOGGER_LOGGABLE_H
