#include "LogLevel.hpp"

namespace Log
{
    std::ostream &operator<<(std::ostream &os, const LogLevel &log_level)
    {
        switch (log_level)
        {
        case LogLevel::Trace:
            os << "TRACE";
            break;
        case LogLevel::Debug:
            os << "DEBUG";
            break;
        case LogLevel::Info:
            os << "INFO";
            break;
        case LogLevel::Warning:
            os << "WARNING";
            break;
        case LogLevel::Error:
            os << "ERROR";
            break;
        case LogLevel::Fatal:
            os << "FATAL";
            break;
        }
        return os;
    }
} // namespace Log
