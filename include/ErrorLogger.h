#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string.h>

/**
 * TRACE == 1
 * DEBUG == 2
 * WARN == 3
 * ERROR == 4
 * FATAL == 5
 */

namespace Utils
{
class ErrorLogger
{
  public:
    static ErrorLogger& getInstance()
    {
        static ErrorLogger _instance;

        return _instance;
    }

    void log(const std::string& logString)
    {
        auto currentTime = std::chrono::system_clock::now();
        std::time_t now = std::chrono::system_clock::to_time_t(currentTime);

        m_file.open(m_filename, std::ios::app);

        std::string output;
        output = output + strtok(ctime(&now), "\n") + logString + "\n";
        if (!m_canWriteToFile || !m_file)
        {
            std::cout << output;
            m_canWriteToFile = false;
            return;
        }
        m_file << output;
        m_file.close();
    }

  private:
    ErrorLogger(std::string filename = "output.log")
        : m_filename(filename), m_file(), m_canWriteToFile(false)
    {
        m_file.open(m_filename, std::ios::out);
        if (!m_file)
        {
            std::cout << "Failed to open " << m_filename << "\n";
        }

        m_canWriteToFile = true;
        m_file.close();
    }
    ~ErrorLogger()
    {
        if (m_file.is_open())
        {
            m_file.close();
        }
    }
    ErrorLogger(const ErrorLogger& other) = delete;
    void operator=(const ErrorLogger& rhs) = delete;

    std::string m_filename;
    std::fstream m_file;
    bool m_canWriteToFile;
};

} // namespace Utils

#if LOG_LEVEL <= 1
/**
 * @brief Logs at log level 1 or below. Use to trace a path through code
 * execution
 *
 * @param message must be able to convert to std::string
 */
#define TRACE(message)                                                         \
    {                                                                          \
        std::string output = "[TRACE]\t\t" + std::string(message) + ": " +     \
                             __FILE__ + "[" + std::to_string(__LINE__) + "]";  \
        Utils::ErrorLogger::getInstance().log(output);                         \
    }
#else
#define TRACE(message) ;
#endif

#if LOG_LEVEL <= 2
/**
 * @brief Logs at log level 2 or below. Use for debugging
 *
 * @param message must be able to convert to std::string
 */
#define DEBUG(message)                                                         \
    {                                                                          \
        std::string output = "[DEBUG]\t\t" + std::string(message) + ": " +     \
                             __FILE__ + "[" + std::to_string(__LINE__) + "]";  \
        Utils::ErrorLogger::getInstance().log(output);                         \
    }
#else
#define DEBUG(message) ;
#endif

#if LOG_LEVEL <= 3
/**
 * @brief Logs at log level 3 or below. Use when code execution can continue,
 * but will likely be impacted
 *
 * @param message must be able to convert to std::string
 */
#define WARN(message)                                                          \
    {                                                                          \
        std::string output = "[WARN]\t\t" + std::string(message) + ": " +      \
                             __FILE__ + "[" + std::to_string(__LINE__) + "]";  \
        Utils::ErrorLogger::getInstance().log(output);                         \
    }
#else
#define WARN(message) ;
#endif

#if LOG_LEVEL <= 4
/**
 * @brief Logs at log level 4 or below. Use when code execution can likely
 * continue, but may be severely affected
 *
 * @param message must be able to convert to std::string
 */
#define ERROR(message)                                                         \
    {                                                                          \
        std::string output = "[ERROR]\t\t" + std::string(message) + ": " +     \
                             __FILE__ + "[" + std::to_string(__LINE__) + "]";  \
        Utils::ErrorLogger::getInstance().log(output);                         \
    }
#else
#define ERROR(message) ;
#endif

/**
 * @brief Logs at any log level. Use when code execution cannot continue
 *
 * @param message must be able to convert to std::string
 */
#define FATAL(message)                                                         \
    {                                                                          \
        std::string output = "[FATAL]\t\t" + std::string(message) + ": " +     \
                             __FILE__ + "[" + std::to_string(__LINE__) + "]";  \
        Utils::ErrorLogger::getInstance().log(output);                         \
    }

#endif // ERRORLOGGER_H