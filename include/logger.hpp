#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace calc_utility {

class Logger {
  public:
    static Logger &instance();

    spdlog::logger *get() const;

    void info(const char *msg) const;
    void error(const char *msg) const;

    template <typename... Args> void info(const char *fmt, Args &&...args) const;

    template <typename... Args> void error(const char *fmt, Args &&...args) const;

  private:
    Logger();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

  private:
    spdlog::logger *logger_;
};

template <typename... Args> inline void Logger::info(const char *fmt, Args &&...args) const {
    logger_->info(fmt, std::forward<Args>(args)...);
}

template <typename... Args> inline void Logger::error(const char *fmt, Args &&...args) const {
    logger_->error(fmt, std::forward<Args>(args)...);
}

} // namespace calc_utility
