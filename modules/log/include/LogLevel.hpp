#ifndef LOG_LEVEL_H_
#define LOG_LEVEL_H_

#include <ostream>
#include <stdint.h>

namespace Log
{
    enum class LogLevel : uint8_t
    {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    };

    std::ostream &operator<<(std::ostream &os, const LogLevel &log_level);
} // namespace Log

#endif