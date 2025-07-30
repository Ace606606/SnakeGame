// ./src/main_window.cpp
#include "main_window.hpp"

#include <spdlog/spdlog.h>

#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QStatusBar>
#include <QVBoxLayout>

#include "constants.hpp"
#include "game_widget.hpp"
#include "language_manager.hpp"
#include "main_widget.hpp"
#include "option_widget.hpp"
#include "settings_manager.hpp"
#include "ui_factory.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupStatusBar();
    setupConnections();
    // loadMainWindowSettings();
}

// MainWindow::~MainWindow() {  // saveMainWindowSettings();}

void MainWindow::setupUI() {
    m_centralWidgetContainer = new QWidget(this);
    m_centralWidgetContainer->setObjectName(
        "MainWindow_m_centralWidgetContainer");

    m_centralLayout = new QVBoxLayout(m_centralWidgetContainer);
    m_centralWidgetContainer->setLayout(m_centralLayout);

    setCentralWidget(m_centralWidgetContainer);

    m_stack = new QStackedWidget(m_centralWidgetContainer);

    m_mainWidget = new MainWidget(this);
    m_gameWidget = new GameWidget(this);
    m_optionWidget = new OptionWidget(this);

    m_stack->addWidget(m_mainWidget);
    m_stack->addWidget(m_gameWidget);
    m_stack->addWidget(m_optionWidget);

    m_centralLayout->addWidget(m_stack);

    m_stack->setCurrentWidget(m_mainWidget);
}

void MainWindow::setupStatusBar() {
    m_statusBar = new QStatusBar(this);
    setStatusBar(m_statusBar);

    m_statusLabelBar = UiFactory::createInfoLabel(tr("Ready"), m_statusBar);
}

void MainWindow::setupConnections() {
    connect(m_mainWidget, &MainWidget::startGameClicked, this,
            &MainWindow::onStartGameClicked);
    connect(m_mainWidget, &MainWidget::optionClicked, this,
            &MainWindow::onOptionMenuOpened);
    connect(m_mainWidget, &MainWidget::exitClicked, this,
            &MainWindow::onExitAppClicked);

    connect(m_optionWidget, &OptionWidget::backToMainMenu, this,
            &MainWindow::onBackToMainMenu);
    connect(m_optionWidget, &OptionWidget::settingsChangedAndSaved, this,
            &MainWindow::handleGameSettingsChanged);
    connect(m_optionWidget, &OptionWidget::requestLanguageChange, this,
            &MainWindow::handleChangeLanguage);
}

void MainWindow::retranslateUI() {
    if (m_statusLabelBar) {
        m_statusLabelBar->setText(tr("Ready"));
    }
    if (m_mainWidget) m_mainWidget->retranslateUi();
}

void MainWindow::onStartGameClicked() {
    SPDLOG_DEBUG("The start button is pressed");

    // m_gameWidget->setSpeed(m_optionWidget->getSpeed());
    // m_gameWidget->setWallCrossing(m_optionWidget->isWallCrossingAllowed());
    m_gameWidget->startGame();
    m_gameWidget->setFocus();

    m_stack->setCurrentWidget(m_gameWidget);
}

void MainWindow::onOptionMenuOpened() {
    SPDLOG_DEBUG("The Option button is pressed");
    m_optionWidget->loadSettings();
    m_stack->setCurrentWidget(m_optionWidget);
}

void MainWindow::onExitAppClicked() {
    QMessageBox::StandardButton reply;
    SPDLOG_DEBUG("The Exit button is pressed");

    reply = QMessageBox::question(this, "Confirm Exit",
                                  "Are you sure want to exit?",
                                  QMessageBox::No | QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::onBackToMainMenu() {
    SPDLOG_DEBUG("The BackToMainMenu button is pressed");
    m_stack->setCurrentWidget(m_mainWidget);
}

void MainWindow::handleChangeLanguage(const QString &languageCode) {
    LanguageManager::instance().setLanguage(languageCode);
    SPDLOG_INFO("Language changed to {}", languageCode.toStdString());
}

void MainWindow::handleGameSettingsChanged() {
    SPDLOG_DEBUG("Game settings have been changed and saved.");
}

// void MainWindow::loadMainWindowSettings() {
// }

// void MainWindow::saveMainWindowSettings() {
// }