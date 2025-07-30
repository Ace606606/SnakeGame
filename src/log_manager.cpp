// ./include/log_manager.hpp

#include "log_manager.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QString>
#include <chrono>
#include <memory>
#include <vector>

#include "constants.hpp"

void customMessageOutput(QtMsgType type, const QMessageLogContext& context,
                         const QString& msg) {
    std::string s_msg = msg.toStdString();
    std::string s_file = context.function ? context.file : "unknown_file";
    std::string s_function =
        context.function ? context.function : "unknown_function";
    int line = context.line;

    spdlog::level::level_enum spd_level;
    spd_level = AppConstants::Logging::mapQtMsgTypeToSpdlogLevel(type);

    auto logger = spdlog::default_logger_raw();
    if (logger) {
        logger->log(
            spdlog::source_loc{s_file.c_str(), line, s_function.c_str()},
            spd_level, "{}", s_msg);
    } else {
        fprintf(stderr, "Pre-spdlog Qt message [%s:%d,%s]: %s\n",
                s_file.c_str(), line, s_function.c_str(), s_msg.c_str());
    }

    if (type == QtFatalMsg) {
        abort();
    }
}

LogManager& LogManager::instance() {
    static LogManager instance;
    return instance;
}

LogManager::LogManager(QObject* parent) : QObject(parent) {
    qDebug() << "LogManager: Instance created. Awaiting spdlog initialization.";
}

LogManager::~LogManager() {
    //  spdlog::shutdown();
}

std::vector<spdlog::sink_ptr> LogManager::createSinks(
    spdlog::level::level_enum consoleLevel, bool logToConsole,
    spdlog::level::level_enum fileLevel, bool logToFile,
    const QString& logDirPath, const QString& logFileName) {
    std::vector<spdlog::sink_ptr> sinks;

    if (logToConsole) {
        auto console_sink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(consoleLevel);
        console_sink->set_pattern(
            "[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%P] [%t] [%s:%#,%!] %v");
        sinks.push_back(console_sink);
    }

    if (logToFile) {
        QDir logDir(logDirPath);
        if (!logDir.exists()) {
            logDir.mkpath(".");
        }

        QString fullLogFilePath = logDirPath + "/" + logFileName;
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            fullLogFilePath.toStdString(), 1024 * 1024 * 5, 3);
        file_sink->set_pattern(
            "[%Y-%m-%d %H:%M:%S.%e] [%l] [%P] [%t] [%s:%#,%!] %v");
        sinks.push_back(file_sink);
    }
    return sinks;
}

void LogManager::initializeDefaultLogger(
    const QString& loggerName, spdlog::level::level_enum consoleLevel,
    bool logToConsole, spdlog::level::level_enum fileLevel, bool logToFile,
    const QString& logDirPath, const QString& logFileName) {
    std::vector<spdlog::sink_ptr> sinks =
        createSinks(consoleLevel, logToConsole, fileLevel, logToFile,
                    logDirPath, logFileName);

    auto logger = std::make_shared<spdlog::logger>(loggerName.toStdString(),
                                                   sinks.begin(), sinks.end());

    spdlog::set_default_logger(logger);
    spdlog::flush_every(std::chrono::seconds(1));

    SPDLOG_INFO("Spdlog default logger '{}' initialized. Console: {}, File: {}",
                loggerName.toStdString(), logToConsole ? "Enabled" : "Disabled",
                logToFile ? "Enabled" : "Disabled");
}

std::shared_ptr<spdlog::logger> LogManager::createLogger(
    const QString& loggerName, spdlog::level::level_enum consoleLevel,
    bool logToConsole, spdlog::level::level_enum fileLevel, bool logToFile,
    const QString& logDirPath, const QString& logFileName) {
    if (spdlog::get(loggerName.toStdString())) {
        SPDLOG_WARN(
            "Logger with name '{}' already exists. Returning existing logger.",
            loggerName.toStdString());
        return spdlog::get(loggerName.toStdString());
    }

    std::vector<spdlog::sink_ptr> sinks =
        createSinks(consoleLevel, logToConsole, fileLevel, logToFile,
                    logDirPath, logFileName);

    auto logger = std::make_shared<spdlog::logger>(loggerName.toStdString(),
                                                   sinks.begin(), sinks.end());

    logger->set_level(spdlog::level::trace);
    spdlog::register_logger(logger);
    m_loggers[loggerName] = logger;

    SPDLOG_INFO("Created new spdlog logger '{}'. Console: {}, File: {}",
                loggerName.toStdString(), logToConsole ? "Enabled" : "Disabled",
                logToFile ? "Enabled" : "Disable");
    return logger;
}

void LogManager::setLoggerSinkLevels(const QString& loggerName,
                                     spdlog::level::level_enum consoleLevel,
                                     spdlog::level::level_enum fileLevel) {
    auto logger = spdlog::get(loggerName.toStdString());

    if (logger) {
        for (auto& sink : logger->sinks()) {
            if (auto console_sink = std::dynamic_pointer_cast<
                    spdlog::sinks::stdout_color_sink_mt>(sink)) {
                console_sink->set_level(consoleLevel);
            } else if (auto file_sink = std::dynamic_pointer_cast<
                           spdlog::sinks::rotating_file_sink_mt>(sink)) {
                file_sink->set_level(fileLevel);
            }
        }
        SPDLOG_INFO("lOGGER '{}' sin levels set. Console: {}, File: {}",
                    loggerName.toStdString(),
                    spdlog::level::to_string_view(consoleLevel),
                    spdlog::level::to_string_view(fileLevel));
    } else {
        SPDLOG_WARN("Logger '{}' not found for sink level change",
                    loggerName.toStdString());
    }
}

void LogManager::setLoggerEnabledState(const QString& loggerName,
                                       bool consoleEnabled, bool fileEnabled) {
    auto logger = spdlog::get(loggerName.toStdString());
    if (logger) {
        for (auto& sink : logger->sinks()) {
            if (auto console_sink = std::dynamic_pointer_cast<
                    spdlog::sinks::stdout_color_sink_mt>(sink)) {
                console_sink->set_level(consoleEnabled ? spdlog::level::trace
                                                       : spdlog::level::off);
            }
            if (auto file_sink = std::dynamic_pointer_cast<
                    spdlog::sinks::rotating_file_sink_mt>(sink)) {
                file_sink->set_level(fileEnabled ? spdlog::level::trace
                                                 : spdlog::level::off);
            }
        }
        SPDLOG_INFO("Logger '{}' output states set. Console: {}, File: {}",
                    loggerName.toStdString(),
                    consoleEnabled ? "Enabled" : "Disabled",
                    fileEnabled ? "Enabled" : "Disabled");
    } else {
        SPDLOG_WARN("Logger '{}' not found for enabled state change.",
                    loggerName.toStdString());
    }
}
