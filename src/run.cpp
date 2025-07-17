#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "constants.hpp"
#include "mainWindow.hpp"

void load_style(QApplication& app) {
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

void config_window(QApplication& app, MainWindow& window) {
    window.setWindowTitle(app.applicationName());
    window.resize(500, 500);
    window.setStyle(app.setStyle("Fusion"));
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    load_style(app);

    app.setApplicationName(AppConstants::APP_NAME);
    app.setApplicationVersion(AppConstants::APP_VERSION);

    MainWindow window;
    config_window(app, window);
    window.show();

    return app.exec();
}