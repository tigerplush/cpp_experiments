#ifndef LOG_H_
#define LOG_H_

#include "Logger.hpp"
#include "LogLevel.hpp"

using Log::LogLevel;

namespace Log
{
    #define LOG(severity_level) Logger::get_instance().line(severity_level) << __func__ << " "
    #define TRACE LOG(LogLevel::Trace)
    #define DEBUG LOG(LogLevel::Debug)
    #define INFO LOG(LogLevel::Info)
    #define WARNING LOG(LogLevel::Warning)
    #define ERROR LOG(LogLevel::Error)
    #define FATAL LOG(LogLevel::Fatal)
} // namespace Log


#endif