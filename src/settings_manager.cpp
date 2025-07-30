// ./include/settings_manager.cpp
#include "settings_manager.hpp"

#include <QCoreApplication>
#include <QDebug>
#include <QString>

#include "constants.hpp"

SettingsManager& SettingsManager::instance() {
    static SettingsManager instance;
    return instance;
}

SettingsManager::SettingsManager(QObject* parent)
    : QObject(parent),
      m_settings(QCoreApplication::organizationName(),
                 QCoreApplication::applicationName()) {
    if (m_settings.value("SettingsDefault", true).toBool()) {
        initializeFileConfig();
    }
    qDebug() << "SettingsManager: Instance created. Settings file:"
             << m_settings.fileName();
}

void SettingsManager::initializeFileConfig() {
    qDebug() << "SettingsManager: Create settings file:"
             << m_settings.fileName();

    m_settings.setValue("SettingsDefault", false);

    setLogLevelName(AppConstants::Logging::DEFAULT_LOG_LEVEL);
    setLogToConsoleEnabled(AppConstants::Logging::DEFAULT_LOG_TO_CONSOLE);
    setConsoleLogLevelName(AppConstants::Logging::DEFAULT_CONSOLE_LOG_LEVEL);
    setLogToFileEnabled(AppConstants::Logging::DEFAULT_LOG_TO_FILE);
    setFileLogLevelName(AppConstants::Logging::DEFAULT_FILE_LOG_LEVEL);

    setLanguageCode(AppConstants::LanguageCodes::DEFAULT_LANGUAGE);

    setDifficulty(AppConstants::GameSettings::DEFAULT_DIFFICULTY);
    setWallCrossingAllowed(AppConstants::GameSettings::DEFAULT_WALL_CROSSING);

    m_settings.sync();
}

void SettingsManager::setLogLevelName(const QString& levelName) {
    m_settings.setValue("Logging/LevelMain", levelName);
}

void SettingsManager::setLogToConsoleEnabled(bool enabled) {
    m_settings.setValue("Logging/ToConsole", enabled);
}

void SettingsManager::setConsoleLogLevelName(const QString& levelName) {
    m_settings.setValue("Logging/ConsoleLevel", levelName);
    qDebug() << "SettingsManager: Console log level set to " << levelName;
}

void SettingsManager::setLogToFileEnabled(bool enabled) {
    m_settings.setValue("Logging/ToFile", enabled);
}

void SettingsManager::setFileLogLevelName(const QString& levelName) {
    m_settings.setValue("Logging/FileLevel", levelName);
    qDebug() << "SettingsManager: File log level set to " << levelName;
}

void SettingsManager::setLanguageCode(const QString& languageCode) {
    m_settings.setValue("Language", languageCode);
    SPDLOG_DEBUG("Language set to {}", languageCode.toStdString());
}

void SettingsManager::setDifficulty(
    AppConstants::GameSettings::Difficulty difficulty) {
    m_settings.setValue("GameSettings/Difficulty",
                        static_cast<int>(difficulty));
    SPDLOG_DEBUG("Dificulty set to {}", static_cast<int>(difficulty));
}

void SettingsManager::setWallCrossingAllowed(bool allowed) {
    m_settings.setValue("GameSettings/WallCrossing", allowed);
    SPDLOG_DEBUG("Wall Crossing set to {}", allowed);
}

QString SettingsManager::getLogLevelName() const {
    return m_settings
        .value("Logging/LevelMain", AppConstants::Logging::DEFAULT_LOG_LEVEL)
        .toString();
}

bool SettingsManager::getLogToConsoleEnabled() const {
    return m_settings
        .value("Logging/ToConsole",
               AppConstants::Logging::DEFAULT_LOG_TO_CONSOLE)
        .toBool();
}

QString SettingsManager::getConsoleLogLevelName() const {
    return m_settings
        .value("Logging/ConsoleLevel",
               AppConstants::Logging::DEFAULT_CONSOLE_LOG_LEVEL)
        .toString();
}

bool SettingsManager::getLogToFileEnabled() const {
    return m_settings
        .value("Logging/ToFile", AppConstants::Logging::DEFAULT_LOG_TO_FILE)
        .toBool();
}

QString SettingsManager::getFileLogLevelName() const {
    return m_settings
        .value("Logging/FileLevel",
               AppConstants::Logging::DEFAULT_FILE_LOG_LEVEL)
        .toString();
}

QString SettingsManager::getLanguageCode() const {
    return m_settings
        .value("Language", AppConstants::LanguageCodes::DEFAULT_LANGUAGE)
        .toString();
}

AppConstants::GameSettings::Difficulty SettingsManager::getDifficulty() const {
    return static_cast<AppConstants::GameSettings::Difficulty>(
        m_settings
            .value("GameSettings/Difficulty",
                   static_cast<int>(
                       AppConstants::GameSettings::DEFAULT_DIFFICULTY))
            .toInt());
}

bool SettingsManager::getWallCrossingAllowed() const {
    return m_settings
        .value("GameSettings/WallCrossing",
               AppConstants::GameSettings::DEFAULT_WALL_CROSSING)
        .toBool();
}

void SettingsManager::resetToDefaults() {
    qDebug() << "SettingsManager: Resetting all settings to defaults.";
    m_settings.setValue("SettingsDefault", true);
    m_settings.sync();
    initializeFileConfig();
}