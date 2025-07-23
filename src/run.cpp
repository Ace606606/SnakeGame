#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "constants.hpp"
#include "language_manager.hpp"
#include "main_window.hpp"

void loadStyle(QApplication& app) {
    QFile file(":style/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        QString style = in.readAll();
        app.setStyleSheet(style);
        file.close();
    } else {
        qDebug() << "Не удалось загрузить стиль";
    }
}

void configWindow(QApplication& app, MainWindow& window) {
    window.setWindowTitle(app.applicationName());
    window.resize(AppConstants::WINDOW_WIDTH, AppConstants::WINDOW_HEIGHT);
    window.setStyle(app.setStyle("Fusion"));
}

void initLanguageManager(const QString& initialLanguageCode) {
    LanguageManager& languageManager = LanguageManager::instance();
    languageManager.initializeLanguages();
    if (!languageManager.setLanguage(initialLanguageCode)) {
        qWarning() << "Failed to set initial language to" << initialLanguageCode
                   << ". Trying fallback.";
        if (!languageManager.setLanguage(
                AppConstants::LanguageCodes::RUSSIAN_RU)) {
            qWarning() << "Failed to set initial language to Russian either. "
                          "No translations loaded.";
        }
    }
}

int main(int argc, char** argv) {
    qRegisterMetaType<AppConstants::GameSettings::Difficulty>();
    QApplication app(argc, argv);

    initLanguageManager(AppConstants::LanguageCodes::DEFAULT_LANGUAGE);

    loadStyle(app);

    app.setApplicationName(AppConstants::AboutApp::APP_NAME);
    app.setApplicationVersion(AppConstants::AboutApp::VERSION);

    MainWindow window;
    configWindow(app, window);

    window.show();

    return app.exec();
}