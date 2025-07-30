// ./include/log_manager.hpp

#pragma once

#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>

#include <QMap>
#include <QObject>
#include <QtGlobal>
#include <memory>
class QString;

void customMessageOutput(QtMsgType type, const QMessageLogContext& context,
                         const QString& msg);

class LogManager : public QObject {
    Q_OBJECT

   public:
    static LogManager& instance();

    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    void initializeDefaultLogger(const QString& loggerName,
                                 spdlog::level::level_enum consoleLevel,
                                 bool logToConsole,
                                 spdlog::level::level_enum fileLevel,
                                 bool logToFile, const QString& logDirPath,
                                 const QString& logFileName);

    std::shared_ptr<spdlog::logger> createLogger(
        const QString& loggerName, spdlog::level::level_enum consoleLevel,
        bool logToConsole, spdlog::level::level_enum fileLevel, bool logToFile,
        const QString& logDirPath, const QString& logFileName);

    void setLoggerLevel(const QString& loggerName,
                        spdlog::level::level_enum level);
    void setLoggerSinkLevels(const QString& loggerNAme,
                             spdlog::level::level_enum consoleLevel,
                             spdlog::level::level_enum fileLevel);
    void setLoggerEnabledState(const QString& loggerName, bool consoleEnabled,
                               bool fileEnabled);

   private:
    explicit LogManager(QObject* parent = nullptr);
    ~LogManager();

    std::vector<spdlog::sink_ptr> createSinks(
        spdlog::level::level_enum consoleLevel, bool logToConsole,
        spdlog::level::level_enum fileLevel, bool logToFile,
        const QString& logDirPath, const QString& logFileName);

    QMap<QString, std::shared_ptr<spdlog::logger>> m_loggers;
};