// ./inlcude/main_window.hpp
#pragma once

#include <QMainWindow>

class QStackedWidget;
class QVBoxLayout;
class QStatusBar;
class QLabel;
class QPushButton;
class MainWidget;
class GameWidget;
class OptionWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

    void retranslateUI();

   protected:
    void changeEvent(QEvent *event) override;

   private slots:
    void onStartGameClicked();
    void onOptionMenuOpened();
    void onExitAppClicked();

    void onBackToMainMenu();
    void handleChangeLanguage(const QString &languageCode);
    void handleGameSettingsChanged();

   private:
    QWidget *m_centralWidgetContainer = nullptr;
    QVBoxLayout *m_centralLayout = nullptr;
    QStackedWidget *m_stack = nullptr;

    MainWidget *m_mainWidget = nullptr;
    GameWidget *m_gameWidget = nullptr;
    OptionWidget *m_optionWidget = nullptr;

    QStatusBar *m_statusBar = nullptr;
    QLabel *m_statusLabelBar = nullptr;
    QPushButton *m_langRuButton = nullptr;
    QPushButton *m_langEnButton = nullptr;

    void setupUI();
    void setupConnections();
    void setupStatusBar();
    // void loadMainWindowSettings();
    // void saveMainWindowSettings();
};