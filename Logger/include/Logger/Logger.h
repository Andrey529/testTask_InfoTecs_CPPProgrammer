#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H


#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Logger {
public:
    static void Init(const std::string &logPath);

    static std::shared_ptr<spdlog::logger>& getLogger();

private:
    static std::shared_ptr<spdlog::logger> logger_;
};


#endif //LOGGER_LOGGER_H
