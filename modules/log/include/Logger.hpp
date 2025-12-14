#ifndef LOGGER_H_
#define LOGGER_H_

#include <chrono>
#include <iomanip>
#include <iostream>

#include "LogLevel.hpp"

namespace Log
{
    class Logger
    {
    private:
        LogLevel m_log_level = LogLevel::Info;
        static Logger m_instance;

    public:
        class LogLine
        {
        private:
            Logger &m_logger;
            LogLevel m_severity;

        public:
            LogLine(LogLevel t_severity, Logger &t_logger)
                : m_severity(t_severity), m_logger(t_logger)
            {
                m_logger.write_header(m_severity);
            }

            ~LogLine()
            {
                m_logger.end_line(m_severity);
            }

            template <typename T>
            LogLine &operator<<(const T &value)
            {
                m_logger.write(m_severity, value);
                return *this;
            }
        };

        static Logger &get_instance()
        {
            return m_instance;
        }

        template <typename T>
        void write(LogLevel severity, const T &value)
        {
            if (severity >= m_log_level)
            {
                std::cout << value;
            }
        }

        void write_header(LogLevel severity)
        {
            if (severity >= m_log_level)
            {
                std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()) % 1000000;
                time_t time = std::chrono::system_clock::to_time_t(now);
                tm tm = *std::localtime(&time);
                std::cout << std::put_time( &tm, "%Y-%m-%dT%H:%M:%S") << "." << std::setfill('0') << std::setw(6) << ns.count() << "Z";
                std::cout << " " << severity << " ";
            }
        }

        void end_line(LogLevel severity)
        {
            if (severity >= m_log_level)
            {
                std::cout << std::endl;
            }
        }

        LogLine line(LogLevel severity)
        {
            return LogLine(severity, *this);
        }

        void set_log_level(LogLevel log_level)
        {
            m_log_level = log_level;
        }
    };
} // namespace Log

#endif