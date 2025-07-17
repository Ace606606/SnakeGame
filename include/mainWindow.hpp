// ./inlcude/mainWindow.hpp
#pragma once

#include <QLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

#include "gameWidget.hpp"
#include "mainWidget.hpp"
#include "optionWidget.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);

   private:
    void setupCentralWidget();

    void setupConnections();

    void onStartClicked();
    void onOptionClicked();
    void onExitClicked();

    QWidget *mainContainer = nullptr;
    QVBoxLayout *mainLayout = nullptr;

    QStackedWidget *stack = nullptr;

    MainWidget *mainWidget = nullptr;
    GameWidget *gameWidget = nullptr;
    OptionWidget *optionWidget = nullptr;
};