// ./src/mainwindow.cpp
#include "mainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupCentralWidget();
    setupConnections();
}

void MainWindow::setupCentralWidget() {
    mainContainer = new QWidget(this);
    mainLayout = new QVBoxLayout(mainContainer);
    mainContainer->setLayout(mainLayout);
    setCentralWidget(mainContainer);

    stack = new QStackedWidget(mainContainer);

    mainWidget = new MainWidget(this);
    gameWidget = new GameWidget(this);
    optionWidget = new OptionWidget(this);

    stack->addWidget(mainWidget);
    stack->addWidget(gameWidget);
    stack->addWidget(optionWidget);

    mainLayout->addWidget(stack);

    stack->setCurrentWidget(mainWidget);
}

void MainWindow::setupConnections() {
    connect(mainWidget, &MainWidget::startGameClicked, this,
            &MainWindow::onStartClicked);
    connect(mainWidget, &MainWidget::optionClicked, this,
            &MainWindow::onOptionClicked);
    connect(mainWidget, &MainWidget::exitClicked, this,
            &MainWindow::onExitClicked);
}

void MainWindow::onStartClicked() {
    qDebug("The start button is pressed");

    gameWidget->setSpeed(optionWidget->getSpeed());
    gameWidget->setWallCrossing(optionWidget->isWallCrossingAllowed());
    gameWidget->startGame();
    gameWidget->setFocus();

    stack->setCurrentWidget(gameWidget);
}

void MainWindow::onOptionClicked() {
    qDebug("The Option button is pressed");
    stack->setCurrentWidget(optionWidget);
}

void MainWindow::onExitClicked() {
    QMessageBox::StandardButton reply;
    qDebug("The Exit button is pressed");

    reply = QMessageBox::question(this, "Confirm Exit",
                                  "Are you sure want to exit?",
                                  QMessageBox::No | QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}
