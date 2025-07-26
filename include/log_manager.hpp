// ./include/log_manager.hpp

#pragma once

#include <QFile>
#include <QObject>
#include <QTextStream>

void customMessageOutput(QtMsgType type, const QMessageLogContext& context,
                         const QString& msg);

class LogManager : public QObject {
    Q_OBJECT
   public:
    static LogManager& instance();

    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    void setLogToFileEnabled(bool enabled);
    void setLogToConsoleEnabled(bool enabled);
    void setLogLevel(QtMsgType level);

    void handleMessage(QtMsgType type, const QMessageLogContext& context,
                       const QString& msg);

   private:
    explicit LogManager(QObject* parent = nullptr);
    ~LogManager();

    QFile m_logFile;
    QTextStream m_logStream;
    bool m_logToFileEnabled = false;
    bool m_logToConsoleEnabled = true;
    QtMsgType m_currentLogLevel = QtDebugMsg;
    bool m_isHandlingMessage = false;

    QString getMessageTypeName(QtMsgType type) const;
};