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
    qDebug() << "SettingsManager initialized. Settings file:"
             << m_settings.fileName();
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

QString SettingsManager::getLanguageCode() const {
    return m_settings
        .value("Language", AppConstants::LanguageCodes::DEFAULT_LANGUAGE)
        .toString();
}

void SettingsManager::setDifficulty(
    AppConstants::GameSettings::Difficulty difficulty) {
    m_settings.setValue("GameSettings/Difficulty",
                        static_cast<int>(difficulty));
    qDebug() << "SettingsManager: Dificulty set to"
             << static_cast<int>(difficulty);
}

void SettingsManager::setWallCrossingAllowed(bool allowed) {
    m_settings.setValue("GameSettings/WallCrossing", allowed);
    qDebug() << "SettingsManager: Wall Crossing set to" << allowed;
}

void SettingsManager::setLanguageCode(const QString& languageCode) {
    m_settings.setValue("Language", languageCode);
    qDebug() << "SettingsManager: Language set to" << languageCode;
}

QString SettingsManager::getLogLevelName() const {
    return m_settings
        .value("Logging/Level", AppConstants::Logging::DEFAULT_LOG_LEVEL)
        .toString();
}

bool SettingsManager::getLogToFileEnabled() const {
    return m_settings
        .value("Logging/ToFile", AppConstants::Logging::DEFAULT_LOG_TO_FILE)
        .toBool();
}

bool SettingsManager::getLogToConsoleEnabled() const {
    return m_settings
        .value("Logging/ToConsole",
               AppConstants::Logging::DEFAULT_LOG_TO_CONSOLE)
        .toBool();
}

void SettingsManager::setLogLevelName(const QString& levelName) {
    m_settings.setValue("Logging/Level", levelName);
}

void SettingsManager::setLogToFileEnabled(bool enabled) {
    m_settings.setValue("Logging/ToFile", enabled);
}

void SettingsManager::setLogToConsoleEnabled(bool enabled) {
    m_settings.setValue("Logging/ToConsole", enabled);
}