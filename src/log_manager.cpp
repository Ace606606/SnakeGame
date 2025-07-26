// ./include/log_manager.hpp
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <log_manager.hpp>

#include "constants.hpp"

// void customMessageOutput(QtMsgType type, const QMessageLogContext &context,
//                          const QString &msg) {
//     LogManager::instance().handleMessage(type, context, msg);
// }

LogManager &LogManager::instance() {
    static LogManager instance;
    return instance;
}

LogManager::LogManager(QObject *parent)
    : QObject(parent), m_isHandlingMessage(false) {
    // QString logDirPath =
    //     QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)
    //     +
    //     "/logs";
    // QDir logDir(logDirPath);
    // if (!logDir.exists()) {
    //     fprintf(stderr, "LogManager: Create log directory: %s\n",
    //             logDir.path().toUtf8().constData());
    //     logDir.mkpath(".");
    // }

    // QString logFilePath =
    //     logDirPath + "/" + AppConstants::AboutApp::APP_NAME + ".log";
    // m_logFile.setFileName(logFilePath);

    // if (m_logFile.open(QIODevice::WriteOnly | QIODevice::Append |
    //                    QIODevice::Text)) {
    //     m_logStream.setDevice(&m_logFile);
    //     fprintf(stderr, "LogManager: Log file opened at %s\n",
    //             logFilePath.toLocal8Bit().constData());
    // } else {
    //     fprintf(stderr, "LogManager: Could not open log file %s %s\n",
    //             logFilePath.toLocal8Bit().constData(),
    //             m_logFile.errorString().toLocal8Bit().constData());
    //     m_logToFileEnabled = false;
    //     fprintf(stderr, "LogManager: Logging to file is disabled");
    // }
}

LogManager::~LogManager() {
    if (m_logFile.isOpen()) {
        m_logStream << QDateTime::currentDateTime().toString(
                           "yyyy-MM--dd hh:mm::ss")
                    << " [INFO ] LogManager:: Application shutting down. Log "
                       "file closed."
                    << Qt::endl;
        m_logFile.close();
    }
    qInstallMessageHandler(0);
}

void LogManager::setLogToFileEnabled(bool enabled) {
    m_logToFileEnabled = enabled;
    qDebug() << "LogManager: Log file set to" << (enabled ? "true" : "false");
}

void LogManager::setLogToConsoleEnabled(bool enabled) {
    m_logToConsoleEnabled = enabled;
    qDebug() << "LogManager: Log console set to"
             << (enabled ? "true" : "false");
}

void LogManager::setLogLevel(QtMsgType level) {
    m_currentLogLevel = level;
    qDebug() << "LogManager: Log level set to" << getMessageTypeName(level);
}

void LogManager::handleMessage(QtMsgType type,
                               const QMessageLogContext &context,
                               const QString &msg) {
    if (m_isHandlingMessage) {
        return;
    }

    m_isHandlingMessage = true;

    if (type < m_currentLogLevel) {
        m_isHandlingMessage = false;
        return;
    }

    QString file = "unknown";
    int line = 0;
    QString function = "unknown";

    if (context.file) {
        file = QString(context.file);
        // Убираем полный путь, оставляем только имя файла
        int lastSlash = file.lastIndexOf('/');
        if (lastSlash != -1) {
            file = file.mid(lastSlash + 1);
        }
    }

    if (context.line) {
        line = context.line;
    }

    if (context.function) {
        function = QString(context.function);
        // Упрощаем сложные сигнатуры функций
        function = function.section('(', 0, 0);  // Убираем параметры
        function = function.section(' ', -1);    // Оставляем только имя функции
    }

    QString message =
        QString("%1 [%2] %3 (%4:%5, %6)")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(getMessageTypeName(type))
            .arg(msg)
            .arg(file)
            .arg(line)
            .arg(function);

    if (m_logToConsoleEnabled) {
        fprintf(stderr, "%s\n", message.toLocal8Bit().constData());
        fflush(stderr);
    }

    if (m_logToFileEnabled && m_logFile.isOpen()) {
        m_logStream << message << Qt::endl;
        m_logStream.flush();
    }

    m_isHandlingMessage = false;
}

QString LogManager::getMessageTypeName(QtMsgType type) const {
    switch (type) {
        case QtDebugMsg:
            return "DEBUG";
        case QtInfoMsg:
            return "INFO ";
        case QtWarningMsg:
            return "WARN ";
        case QtCriticalMsg:
            return "CRIT ";
        case QtFatalMsg:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}