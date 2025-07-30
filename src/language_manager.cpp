// ./src/language_manager.cpp

#include <QApplication>
#include <QDebug>
#include <language_manager.hpp>

#include "constants.hpp"

LanguageManager::LanguageManager() : m_currentLanguage("") {
    SPDLOG_DEBUG("Instance created.");
}

void LanguageManager::initializeLanguages() {
    m_availableLanguages[AppConstants::LanguageCodes::ENGLISH_US] = "";
    m_availableLanguages[AppConstants::LanguageCodes::RUSSIAN_RU] =
        AppConstants::LanguageCodes::PATH_TO_RUS_QM;

    SPDLOG_DEBUG("Initialized with available languages: {}",
                 m_availableLanguages.keys().join(", ").toStdString());
}

bool LanguageManager::setLanguage(const QString &languageCode) {
    QApplication *app =
        qobject_cast<QApplication *>(QCoreApplication::instance());

    if (!app) {
        SPDLOG_WARN("No QApplication instance found!");
        return false;
    }

    if (m_currentLanguage == languageCode) {
        SPDLOG_DEBUG("Language already set to {}", languageCode.toStdString());
        return true;
    }

    if (languageCode == AppConstants::LanguageCodes::ENGLISH_US) {
        if (m_appTranslator) {
            app->removeTranslator(m_appTranslator.get());
            m_appTranslator.reset();
            SPDLOG_DEBUG("Removed previos translator for {}",
                         m_currentLanguage.toStdString());
        }
        m_currentLanguage = AppConstants::LanguageCodes::ENGLISH_US;
        // emit languageChanged(AppConstants::LanguageCodes::ENGLISH_US);
        SPDLOG_DEBUG("Set language to default {}",
                     AppConstants::LanguageCodes::ENGLISH_US.toStdString(),
                     " no translator loaded.");
        return true;
    }

    if (!m_availableLanguages.contains(languageCode)) {
        SPDLOG_WARN("Language code {}", languageCode.toStdString(),
                    " not found in available languages.");
        return false;
    }

    if (m_appTranslator) {
        app->removeTranslator(m_appTranslator.get());
        m_appTranslator.reset();
        SPDLOG_DEBUG("Removed previos translator for {}",
                     m_currentLanguage.toStdString());
    }

    m_appTranslator = std::make_unique<QTranslator>();
    QString qmFilePath = m_availableLanguages.value(languageCode);
    if (m_appTranslator->load(qmFilePath)) {
        app->installTranslator(m_appTranslator.get());
        m_currentLanguage = languageCode;
        SPDLOG_DEBUG(
            "Successfully loaded and installed "
            "translator for {}",
            languageCode.toStdString());

        // emit languageChanged(languageCode);

        return true;
    } else {
        SPDLOG_WARN("Failed to load .qm file for {}",
                    languageCode.toStdString());
        m_currentLanguage = "";
        return false;
    }
}