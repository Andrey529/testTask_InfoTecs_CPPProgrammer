#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::logger_;

void Logger::Init(const std::string &logPath) {
    auto logFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath);
    auto logConsoleSink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    logger_ = std::make_shared<spdlog::logger>("main");
    logger_->sinks().push_back(logFileSink);
}

std::shared_ptr<spdlog::logger> &Logger::getLogger() {
    return logger_;
}
