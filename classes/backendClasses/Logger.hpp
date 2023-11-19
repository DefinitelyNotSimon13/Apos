/**
 * @file logger.cpp
 * @author Simon Blum
 * @date 19.11.2023
 * @version VERSION
 * @license LGPL-V3
 * @brief This header file defines the Logger class for logging messages.
 *
 * @details The Logger class provides methods for logging messages with different severity levels.
 *          It supports logging messages with or without a timestamp, and can optionally show the elapsed time since the logger was created.
 *          The log messages are written to a file and also outputted using qDebug().
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see QFile
 * @see QTextStream
 * @see QDateTime
 * @see QException
 * @see QElapsedTimer
 */

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QException>
#include <QElapsedTimer>

#pragma once

namespace AposLogger {

    /**
     * @class Logger
     * @brief This class provides methods for logging messages with different severity levels.
     *
     * @details The Logger class supports logging messages with or without a timestamp,
     * and can optionally show the elapsed time since the logger was created.
     * The log messages are written to a file and also outputted using qDebug().
     *
     */
    class Logger {
    public:

        /**
         * @brief Constructs a Logger object.
         * @ingroup Constructructors-Destructors
         *
         * @details This constructor initializes the Logger object, starts the timer, and opens the log file.
         */
        Logger();

        /**
         * @brief Destroys the Logger object.
         * @ingroup Constructructors-Destructors
         *
         * @details This destructor performs any necessary cleanup tasks.
         */
        ~Logger();

        /**
         * @brief Logs a message.
         * @ingroup Utility-Functions
         *
         * @details This method logs a message with the current date and time.
         */
        void log();

        /**
         * @brief Logs a message.
         * @ingroup Utility-Functions
         *
         * @param message The message to log.
         *
         * @details This method logs a message with the current date and time.
         */
        void log(const QString &message);

        /**
         * @brief Logs a message and optionally shows the elapsed time.
         * @ingroup Utility-Functions
         *
         * @param message The message to log.
         * @param showTimer Whether to show the elapsed time since the logger was created.
         *
         * @details This method logs a message with the current date and time, and optionally shows the elapsed time.
         */
        void log(const QString &message, bool showTimer);

        /**
         * @brief Logs a message with a specified type.
         * @ingroup Utility-Functions
         *
         * @param type The type of the message.
         * @param message The message to log.
         *
         * @details This method logs a message with a specified type and the current date and time.
         */
        void log(const QString &type, const QString &message);

        /**
         * @brief Logs a message with a specified type, function, file, and line.
         * @ingroup Utility-Functions
         *
         * @param type The type of the message.
         * @param message The message to log.
         * @param function The function where the message was logged.
         * @param file The file where the message was logged.
         * @param line The line where the message was logged.
         *
         * @details This method logs a message with a specified type, function, file, and line, and the current date and time.
         */
        void log(const QString &type, const QString &message, const QString &function);

        /**
         * @brief Logs a message with a specified type, function, file, and line, and optionally shows the elapsed time.
         * @ingroup Utility-Functions
         *
         * @param type The type of the message.
         * @param message The message to log.
         * @param function The function where the message was logged.
         * @param file The file where the message was logged.
         * @param line The line where the message was logged.
         * @param showTimer Whether to show the elapsed time since the logger was created.
         *
         * @details This method logs a message with a specified type, function, file, and line, and the current date and time, and optionally shows the elapsed time.
         */
        void log(const QString &type, const QString &message, const QString &function, const QString &file,
                 const QString &line, bool showTimer = true);

        /**
         * @brief Logs an error message.
         * @ingroup Utility-Functions
         *
         * @details This method logs an error message with the current date and time.
         */
        void error();

        /**
         * @brief Logs an error message with a specified function, file, and line.
         * @ingroup Utility-Functions
         *
         * @param message The error message to log.
         * @param function The function where the error occurred.
         * @param file The file where the error occurred.
         * @param line The line where the error occurred.
         *
         * @details This method logs an error message with a specified function, file, and line, and the current date and time.
         */
        void error(const QString &message, const QString &function, const QString &file,
                   const QString &line);

    private:
        /**
         * @brief Opens the log file.
         * @ingroup Initialization
         *
         * @details This method opens the log file and writes an initialization message to it.
         */
        void openFile();

        /**
         * @brief Starts the timer.
         * @ingroup Utility-Functions
         *
         * @details This method starts the timer used for measuring the elapsed time.
         */
        void startTimer();

        bool fileOpen; ///< Whether the log file is open.
        QSharedPointer<QFile> ptrFile; ///< The log file.
        QSharedPointer<QElapsedTimer> ptrTimer; ///< The timer used for measuring the elapsed time.
        QSharedPointer<QTextStream> ptrLog; ///< The text stream used for writing to the log file.

        /**
         * @brief Returns the current date and time as a string.
         * @ingroup Utility-Functions
         *
         * @return The current date and time as a string.
         */
        static QString currentTime();
    };

} // AposLogger