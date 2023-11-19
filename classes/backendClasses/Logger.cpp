/**
 * @file Logger.cpp
 * @author Simon Blum
 * @date 19.11.2023
 * @version VERSION
 * @license LGPL-V3
 * @brief This source file implements the Logger class for logging messages.
 *
 * @details The Logger class provides methods for logging messages with different severity levels.
 *          It supports logging messages with or without a timestamp, and can optionally show the elapsed time since the logger was created.
 *          The log messages are written to a file and also outputted using qDebug().
 *
 * @note The application is part of a student project and is not intended for commercial use.
 *
 * @see Logger.hpp
 */

#include "Logger.hpp"

namespace AposLogger {
    Logger::Logger() {
        startTimer();

        fileOpen = false;
        ptrFile = QSharedPointer<QFile>(new QFile("aposLog.txt"));

        if (!ptrFile->open(QIODevice::Truncate | QIODevice::WriteOnly)) {
            qDebug() << "Error opening file";
            throw QException();
        } else {
            openFile();
        }

    }

    void Logger::startTimer() {
        ptrTimer = QSharedPointer<QElapsedTimer>(new QElapsedTimer());
        ptrTimer->start();
    }

    void Logger::openFile() {
        ptrLog = QSharedPointer<QTextStream>(new QTextStream(ptrFile.data()));

        *ptrLog << "Log |" << currentTime() << " - AposLog file initialized | " << ptrTimer->elapsed() << "ms"
                << Qt::endl;
        qDebug() << "Log |" << currentTime() << " - AposLog file initialized" << ptrTimer->elapsed() << "ms";

        fileOpen = true;
    }

    QString Logger::currentTime() { return QDateTime::currentDateTime().toString(); }

    Logger::~Logger() {
        *ptrLog << "Log |" << currentTime() << " - AposLogger beeing destroyed | " << ptrTimer->elapsed() << "ms"
                << Qt::endl;
        *ptrLog << "Log |" << currentTime() << " - AposLog closing | " << ptrTimer->elapsed() << "ms" << Qt::endl;

        ptrTimer->invalidate();

        if (ptrFile->isOpen()) {
            ptrFile->close();
        }

        qDebug() << "Log |" << currentTime() << " - AposLogger destroyed";
    }

    void Logger::log() {
        if (!fileOpen) {
            qDebug() << "Error: File not open";
            return;
        }

        QString outMessage =
                "Log |" + currentTime() + " - AposLog | Logged | " + QString::number(ptrTimer->elapsed()) + "ms ";
        *ptrLog << outMessage << Qt::endl;
        qDebug() << outMessage;
    }

    void Logger::log(const QString &message) {
        if (!fileOpen) {
            qDebug() << "Error: File not open";
            return;
        }

        QString outMessage =
                "Log |" + currentTime() + " - AposLog | " + message + " | " + QString::number(ptrTimer->elapsed()) +
                "ms";

        *ptrLog << outMessage << Qt::endl;
        qDebug() << outMessage;
    }

    void Logger::log(const QString &message, bool showTimer) {
        if (!fileOpen) {
            qDebug() << "Error: File not open";
            return;
        }

        QString outMessage = "Log |" + currentTime() + " - AposLog | " + message;

        if (showTimer) {
            outMessage += " | " + QString::number(ptrTimer->elapsed()) + "ms";
        }

        *ptrLog << outMessage << Qt::endl;
        qDebug() << outMessage;
    }

    void Logger::log(const QString &type, const QString &message) {
        if (!fileOpen) {
            qDebug() << "Error: File not open";
            return;
        }

        QString outMessage =
                type + " |" + currentTime() + " - AposLog | " + message + " | " + QString::number(ptrTimer->elapsed()) +
                "ms";

        *ptrLog << outMessage << Qt::endl;
        qDebug() << outMessage;
    }

    void Logger::log(const QString &type, const QString &message, const QString &function) {
        if (!fileOpen) {
            qDebug() << "Error: File not open";
            return;
        }

        QString outMessage =
                type + " |" + currentTime() + " - AposLog | " + message + " | in function: " + function + " | " +
                QString::number(ptrTimer->elapsed()) + "ms";

        *ptrLog << outMessage << Qt::endl;
        qDebug() << outMessage;


    }

    void Logger::log(const QString &type, const QString &message, const QString &function, const QString &file,
                     const QString &line, bool showTimer) {
        if (!fileOpen) {
            qDebug() << "Error: File not open";
            return;
        }

        QString outMessage = type + " |" + currentTime() + " - AposLog | " + message + " | in function: " + function +
                             " | within file: " + file + " | at line: " + line;

        if (showTimer) {
            outMessage += " | " + QString::number(ptrTimer->elapsed()) + "ms";
        }

        *ptrLog << outMessage << Qt::endl;
        qDebug() << outMessage;
    }

    void Logger::error() {
        if (!fileOpen) {
            qDebug() << "Error: File not open";
            return;
        }

        QString outMessage =
                "ERROR |" + currentTime() + " - AposLog | Error | " + QString::number(ptrTimer->elapsed()) + "ms";

        *ptrLog << outMessage << Qt::endl;
        qDebug() << outMessage;

        throw QException();
    }

    void Logger::error(const QString &message, const QString &function, const QString &file, const QString &line) {
        if (!fileOpen) {
            qDebug() << "Error: File not open";
            return;
        }

        QString outMessage =
                "ERROR |" + currentTime() + " - AposLog | Error | " + message + " | in function: " + function +
                " | within file: " + file + " | at line: " + line + " | " + QString::number(ptrTimer->elapsed()) + "ms";

        *ptrLog << outMessage << Qt::endl;
        qDebug() << outMessage;

        throw QException();
    }


} // AposLogger