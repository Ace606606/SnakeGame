// ./src/main_window.cpp
#include "main_window.hpp"

#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>

#include "constants.hpp"
#include "ui_factory.hpp"

// =====================================================
#include <QEvent>
#include <QStatusBar>
// =====================================================

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupStatusBar();
    setupConnections();
    retranslateUI();
}

void MainWindow::setupUI() {
    m_centralWidgetContainer = new QWidget(this);
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

    m_langEnButton = UiFactory::createStandardButton(
        AppConstants::LanguageCodes::LANGUAGE_NAMES
            [AppConstants::LanguageCodes::ENGLISH_US],
        80, 25, m_statusBar);  // constants
    m_langRuButton = UiFactory::createStandardButton(
        AppConstants::LanguageCodes::LANGUAGE_NAMES
            [AppConstants::LanguageCodes::RUSSIAN_RU],
        80, 25, m_statusBar);  // constants

    m_statusBar->addPermanentWidget(m_langEnButton);
    m_statusBar->addPermanentWidget(m_langRuButton);
}

void MainWindow::setupConnections() {
    connect(m_mainWidget, &MainWidget::startGameClicked, this,
            &MainWindow::onStartClicked);
    connect(m_mainWidget, &MainWidget::optionClicked, this,
            &MainWindow::onOptionClicked);
    connect(m_mainWidget, &MainWidget::exitClicked, this,
            &MainWindow::onExitClicked);
    connect(m_langEnButton, &QPushButton::clicked, this, [this]() {
        LanguageManager::instance().setLanguage(
            AppConstants::LanguageCodes::ENGLISH_US);
    });

    connect(m_langRuButton, &QPushButton::clicked, this, [this]() {
        LanguageManager::instance().setLanguage(
            AppConstants::LanguageCodes::RUSSIAN_RU);
    });
}

void MainWindow::retranslateUI() {
    if (m_statusLabelBar) {
        m_statusLabelBar->setText(tr("Ready"));
    }
    if (m_mainWidget) m_mainWidget->retranslateUi();
}

void MainWindow::onStartClicked() {
    qDebug("The start button is pressed");

    m_gameWidget->setSpeed(m_optionWidget->getSpeed());
    m_gameWidget->setWallCrossing(m_optionWidget->isWallCrossingAllowed());
    m_gameWidget->startGame();
    m_gameWidget->setFocus();

    m_stack->setCurrentWidget(m_gameWidget);
}

void MainWindow::onOptionClicked() {
    qDebug("The Option button is pressed");
    m_stack->setCurrentWidget(m_optionWidget);
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

void MainWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        retranslateUI();
    }
    QMainWindow::changeEvent(event);
}