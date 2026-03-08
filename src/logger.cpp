#include "logger.hpp"

namespace calc_utility {

Logger &Logger::instance() {
    static Logger instance;
    return instance;
}

spdlog::logger *Logger::get() const {
    return logger_;
}

void Logger::info(const char *msg) const {
    logger_->info(msg);
}

void Logger::error(const char *msg) const {
    logger_->error(msg);
}

Logger::Logger() {
    auto sp_logger = spdlog::stdout_color_mt("calculator");
    logger_ = sp_logger.get();
    logger_->set_pattern("[%H:%M:%S] [%^%l%$] %v");
    logger_->set_level(spdlog::level::info);
}

Logger::~Logger() {
    spdlog::shutdown();
}

} // namespace calc_utility
