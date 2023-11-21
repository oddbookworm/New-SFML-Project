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
/**
 * @brief Singleton class for logging errors to file (or if file handling fails, console)
 */
class ErrorLogger
{
  public:
    /**
     * @brief Gets the instance of the ErrorLogger singleton
     *
     * @return ErrorLogger& a reference to the singleton
     */
    static ErrorLogger& getInstance()
    {
        static ErrorLogger _instance;

        return _instance;
    }

    /**
     * @brief logs the given string with a timestamp that looks like "Mon Nov 20
     * 23:28:22 2023"
     *
     * @param logString the string to log
     */
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
    /**
     * @brief Private constructor for the singleton design
     *
     * @param filename optional param to set the logfile name, defaults to
     * "output.log"
     */
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

    /**
     * @brief Private destructor for singleton pattern. Ensures that internal
     * files are closed
     */
    ~ErrorLogger()
    {
        if (m_file.is_open())
        {
            m_file.close();
        }
    }

    /**
     * @brief Deleted copy constructor, should not copy singleton
     */
    ErrorLogger(const ErrorLogger& other) = delete;

    /**
     * @brief Deleted assignment operator, should not try to assign singleton
     */
    void operator=(const ErrorLogger& rhs) = delete;

    std::string m_filename; //!< logfile name
    std::fstream m_file;    //!< internal file object
    bool m_canWriteToFile;  //!< true if there has been no issue opening the
                            //!< file, false if there has been
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
#endif // LOG_LEVEL <= 1

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
#endif // LOG_LEVEL <= 2

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
#endif // LOG_LEVEL <= 3

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
#endif // LOG_LEVEL <= 4

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