// ./src/run.cpp
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

// ======================
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <QDir>
#include <chrono>
#include <vector>
// ======================

#include "constants.hpp"
#include "language_manager.hpp"
#include "main_window.hpp"
#include "settings_manager.hpp"

void customMessageOutput(QtMsgType type, const QMessageLogContext& context,
                         const QString& msg) {
    std::string s_msg = msg.toStdString();
    std::string s_file = context.function ? context.file : "unknown_file";
    std::string s_function =
        context.function ? context.function : "unknown_function";
    int line = context.line;

    spdlog::level::level_enum spd_level;
    switch (type) {
        case QtDebugMsg:
            spd_level = spdlog::level::debug;
            break;
        case QtInfoMsg:
            spd_level = spdlog::level::info;
            break;
        case QtWarningMsg:
            spd_level = spdlog::level::warn;
            break;
        case QtCriticalMsg:
            spd_level = spdlog::level::critical;
            break;
        case QtFatalMsg:
            spd_level = spdlog::level::off;
            spd_level = spdlog::level::critical;
            break;
        default:
            spd_level = spdlog::level::info;
            break;
    }

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

void initializeSpdlog() {
    QString logLevelName = SettingsManager::instance().getLogLevelName();
    bool logToConsoleEnabled =
        SettingsManager::instance().getLogToConsoleEnabled();
    bool logToFileEnabled = SettingsManager::instance().getLogToFileEnabled();

    std::vector<spdlog::sink_ptr> sinks;

    if (logToConsoleEnabled) {
        auto console_sink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::debug);
        console_sink->set_pattern(
            "[%Y-%m-%d %H:%M:%S] [%^%l%$] [%P] [%t] [%s:%#,%!] %v");
        sinks.push_back(console_sink);
    }

    if (logToFileEnabled) {
        QString logDirPath = QStandardPaths::writableLocation(
                                 QStandardPaths::AppLocalDataLocation) +
                             "/logs";
        QDir logDir(logDirPath);
        if (!logDir.exists()) {
            logDir.mkpath(".");
        }

        QString logFilePath =
            logDirPath + "/" + AppConstants::AboutApp::APP_NAME + ".log";
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            logFilePath.toStdString(), 1042 * 1024 * 5, 3);
        file_sink->set_level(spdlog::level::info);
        file_sink->set_pattern(
            "[%Y-%m-%d %H:%M:%S] [%l] [%P] [%t] [%s:%#,%!] %v");
        sinks.push_back(file_sink);
    }

    auto logger = std::make_shared<spdlog::logger>("snake_game_logger",
                                                   sinks.begin(), sinks.end());

    spdlog::level::level_enum spdLogLevel = spdlog::level::debug;

    if (AppConstants::Logging::LOG_LEVEL_MAP.contains(logLevelName)) {
        QtMsgType qtLogLevel =
            AppConstants::Logging::LOG_LEVEL_MAP.value(logLevelName);
        switch (qtLogLevel) {
            case QtDebugMsg:
                spdLogLevel = spdlog::level::debug;
                break;
            case QtInfoMsg:
                spdLogLevel = spdlog::level::info;
                break;
            case QtWarningMsg:
                spdLogLevel = spdlog::level::warn;
                break;
            case QtCriticalMsg:
                spdLogLevel = spdlog::level::critical;
                break;
            case QtFatalMsg:
                spdLogLevel = spdlog::level::off;
                break;
            default:
                spdLogLevel = spdlog::level::info;
                break;
        }

        SettingsManager::instance().setLogLevelName(logLevelName);
        SettingsManager::instance().setLogToConsoleEnabled(logToConsoleEnabled);
        SettingsManager::instance().setLogToFileEnabled(logToFileEnabled);
    }

    logger->set_level(spdLogLevel);
    spdlog::set_default_logger(logger);
    spdlog::flush_every(std::chrono::seconds(1));

    SPDLOG_INFO(
        "Spdlog initialized. log level: {}, File logging: {}, Console logging: "
        "{}",
        logLevelName.toStdString(), logToFileEnabled, logToConsoleEnabled);
}

QtMsgType stringToQtMsgType(const QString& levelName) {
    return AppConstants::Logging::LOG_LEVEL_MAP.value(levelName, QtDebugMsg);
}

void loadStyle(QApplication& app) {
    QFile file(":style/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString style = in.readAll();
        app.setStyleSheet(style);
        file.close();
        SPDLOG_INFO("Successfully loaded application style.");
    } else {
        SPDLOG_WARN(
            "Failed to load application style. File not found or "
            "inaccessible.");
    }
}

void initializeWindow(QApplication& app, MainWindow& window) {
    window.setWindowTitle(app.applicationName());
    window.resize(AppConstants::WINDOW_WIDTH, AppConstants::WINDOW_HEIGHT);
    app.setStyle("Fusion");
    SPDLOG_DEBUG("Main window configured with title: {} and size: {}x{}",
                 window.windowTitle().toStdString(), window.size().width(),
                 window.size().height());
}

void initializeLanguageManager(const QString& initialLanguageCode) {
    LanguageManager& languageManager = LanguageManager::instance();
    languageManager.initializeLanguages();
    if (!languageManager.setLanguage(initialLanguageCode)) {
        SPDLOG_WARN("Failed to set initial language to {}. Trying fallback.",
                    initialLanguageCode.toStdString());
        if (!languageManager.setLanguage(
                AppConstants::LanguageCodes::DEFAULT_LANGUAGE)) {
            SPDLOG_CRITICAL(
                "Failed to set initial language to default either. No "
                "translation loaded.");
        }
    } else {
        SPDLOG_INFO("LanguageManager initialized. Current language: {}",
                    initialLanguageCode.toStdString());
    }
}

int main(int argc, char** argv) {
    QCoreApplication::setOrganizationName(
        AppConstants::AboutApp::ORGANIZATON_NAME);
    QCoreApplication::setApplicationName(AppConstants::AboutApp::APP_NAME);

    initializeSpdlog();

    QApplication app(argc, argv);

    qRegisterMetaType<AppConstants::GameSettings::Difficulty>();

    qInstallMessageHandler(customMessageOutput);

    SPDLOG_INFO("Application starting up. Version: {}",
                AppConstants::AboutApp::VERSION.toStdString());

    QString initialLanguageCode = SettingsManager::instance().getLanguageCode();
    initializeLanguageManager(initialLanguageCode);

    loadStyle(app);

    app.setApplicationName(AppConstants::AboutApp::APP_NAME);
    app.setApplicationVersion(AppConstants::AboutApp::VERSION);

    MainWindow window;
    initializeWindow(app, window);

    window.show();
    SPDLOG_DEBUG("Application event loop started. UI visible.");

    int exitCode = app.exec();

    SPDLOG_INFO("Application shutting down with exit code: {}", exitCode);
    spdlog::shutdown();

    return exitCode;
}