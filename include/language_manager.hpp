// ./src/language_manager.hpp
#pragma once
#include <QHash>
#include <QObject>
#include <QString>
#include <QTranslator>
#include <memory>

class LanguageManager : public QObject {
    Q_OBJECT
   public:
    static LanguageManager& instance() {
        static LanguageManager instance;
        return instance;
    }

    LanguageManager(const LanguageManager&) = delete;
    void operator=(const LanguageManager&) = delete;

    void initializeLanguages();

    Q_INVOKABLE bool setLanguage(const QString& languageCode);

    QString currentLanguage() const { return m_currentLanguage; }

    QStringList availableLanguages() const {
        return m_availableLanguages.keys();
    }

    // signals:

    // void languageChanged(const QString& newLanguageCode);

   private:
    explicit LanguageManager();
    std::unique_ptr<QTranslator> m_appTranslator;
    QString m_currentLanguage;

    QHash<QString, QString> m_availableLanguages;
};