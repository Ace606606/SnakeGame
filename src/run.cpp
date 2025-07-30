// ./src/run.cpp
#include <QApplication>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

#include "constants.hpp"
#include "language_manager.hpp"
#include "log_manager.hpp"
#include "main_window.hpp"
#include "settings_manager.hpp"

void initializeWindow(QApplication& app, MainWindow& window) {
    window.setWindowTitle(app.applicationName());
    window.resize(AppConstants::WINDOW_WIDTH, AppConstants::WINDOW_HEIGHT);
    app.setStyle("Fusion");
    SPDLOG_DEBUG("Main window configured with title: {} and size: {}x{}",
                 window.windowTitle().toStdString(), window.size().width(),
                 window.size().height());
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

void initializeLogger() {
    SettingsManager::instance();
    QString logLevelName = SettingsManager::instance().getLogLevelName();

    bool logToConsoleEnabled =
        SettingsManager::instance().getLogToConsoleEnabled();
    bool logToFileEnabled = SettingsManager::instance().getLogToFileEnabled();

    QString consoleLogLevelName =
        SettingsManager::instance().getConsoleLogLevelName();
    QString fileLogLevelName =
        SettingsManager::instance().getFileLogLevelName();

    spdlog::level::level_enum consoleSpdLevel =
        AppConstants::Logging::SPDLOG_LEVEL_MAP.value(consoleLogLevelName,
                                                      spdlog::level::debug);
    spdlog::level::level_enum fileSpdLevel =
        AppConstants::Logging::SPDLOG_LEVEL_MAP.value(fileLogLevelName,
                                                      spdlog::level::info);

    spdlog::level::level_enum defaultLoggerLevel =
        AppConstants::Logging::SPDLOG_LEVEL_MAP.value(logLevelName,
                                                      spdlog::level::debug);

    LogManager::instance().initializeDefaultLogger(
        "snake_game_logger", consoleSpdLevel, logToConsoleEnabled, fileSpdLevel,
        logToFileEnabled,
        QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) +
            "/logs",
        AppConstants::AboutApp::APP_NAME + ".log");

    spdlog::default_logger()->set_level(defaultLoggerLevel);
    qInstallMessageHandler(customMessageOutput);
}

int main(int argc, char** argv) {
    QCoreApplication::setOrganizationName(
        AppConstants::AboutApp::ORGANIZATON_NAME);
    QCoreApplication::setApplicationName(AppConstants::AboutApp::APP_NAME);

    initializeLogger();

    QApplication app(argc, argv);

    qRegisterMetaType<AppConstants::GameSettings::Difficulty>();

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

    SPDLOG_INFO("Application event loop started. UI visible.");

    int exitCode = app.exec();

    spdlog::shutdown();

    return exitCode;
}