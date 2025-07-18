// ./src/language_manager.cpp

#include <QApplication>
#include <QDebug>
#include <language_manager.hpp>

#include "constants.hpp"

LanguageManager::LanguageManager() : m_currentLanguage("") {}

void LanguageManager::initializeLanguages() {
    m_availableLanguages[AppConstants::LanguageCodes::RUSSIAN_RU] =
        AppConstants::LanguageCodes::PATH_TO_RUS_QM;
    qDebug() << "LanguageManager: Initialized with available languages:"
             << m_availableLanguages.keys();
}

bool LanguageManager::setLanguage(const QString &languageCode) {
    QApplication *app =
        qobject_cast<QApplication *>(QCoreApplication::instance());

    if (!app) {
        qWarning() << "LanguageManager: No QApplication instance found!";
        return false;
    }

    if (m_currentLanguage == languageCode) {
        qDebug() << "LanguageManager: language already set to" << languageCode;
        return true;
    }

    if (languageCode == AppConstants::LanguageCodes::ENGLISH_US) {
        if (m_appTranslator) {
            app->removeTranslator(m_appTranslator.get());
            m_appTranslator.reset();
            qDebug() << "LanguageManager: Removed previos translator for"
                     << m_currentLanguage;
        }
        m_currentLanguage = AppConstants::LanguageCodes::ENGLISH_US;
        // emit languageChanged(AppConstants::LanguageCodes::ENGLISH_US);
        qDebug() << "LanguageManager: Set language to default"
                 << AppConstants::LanguageCodes::ENGLISH_US
                 << " no translator loaded.";
        return true;
    }

    if (!m_availableLanguages.contains(languageCode)) {
        qWarning() << "LanguageManager: Language code" << languageCode
                   << "not found in available languages.";
        return false;
    }

    if (m_appTranslator) {
        app->removeTranslator(m_appTranslator.get());
        m_appTranslator.reset();
        qDebug() << "LanguageManager: Removed previos translator for"
                 << m_currentLanguage;
    }

    m_appTranslator = std::make_unique<QTranslator>();
    QString qmFilePath = m_availableLanguages.value(languageCode);
    if (m_appTranslator->load(qmFilePath)) {
        app->installTranslator(m_appTranslator.get());
        m_currentLanguage = languageCode;
        qDebug() << "LanguageManager: Successfully loaded and installed "
                    "translator for"
                 << languageCode;

        // emit languageChanged(languageCode);

        return true;
    } else {
        qWarning() << "LanguageManager: Failed to load .qm file for"
                   << languageCode;
        m_currentLanguage = "";
        return false;
    }
}