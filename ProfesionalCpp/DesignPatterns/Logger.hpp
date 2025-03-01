#pragma once

#include <fstream>
#include <string>
#include <string_view>
#include <vector>

class Logger final
{
public:
    enum class LogLevel
    {
        Error,
        Info,
        Debug
    };
    
    static Logger& instance();

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;

    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

    void setLogLevel(LogLevel level);
    void log(std::string_view message, LogLevel logLevel);
    void log(const std::vector<std::string>& messages, LogLevel logLevel);

private:
    Logger();
    ~Logger();

    std::string_view getLogLevelString(LogLevel level) const;

    static inline const char* const kLogFileName = "log.out";
    std::ofstream mOutputStream;
    LogLevel mLogLevel = LogLevel::Error;
};