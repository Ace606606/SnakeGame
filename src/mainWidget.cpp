// ./src/mainWidget.cpp

#include "mainWidget.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "constants.hpp"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) { setupMainWidget(); }

void MainWidget::setupMainWidget() {
    mainLayout = new QVBoxLayout(this);
    setupTopPanel();
    setupMiddlePanel();
    setupBottomPanel();

    connect(btnStart, &QPushButton::clicked, this,
            &MainWidget::startGameClicked);
    connect(btnOption, &QPushButton::clicked, this, &MainWidget::optionClicked);
    connect(btnExit, &QPushButton::clicked, this, &MainWidget::exitClicked);
}

void MainWidget::setupTopPanel() {
    topContainer = new QWidget();
    QVBoxLayout *topLayout = new QVBoxLayout(topContainer);
    QLabel *mainLabel = new QLabel(AppConstants::WINDOW_TITLE);
    mainLabel->setObjectName("mainLabel");
    topLayout->addWidget(mainLabel, 0, Qt::AlignHCenter);

    mainLayout->addWidget(topContainer);
}

void MainWidget::setupMiddlePanel() {
    middleContainer = new QWidget();
    QVBoxLayout *middleLayout = new QVBoxLayout(middleContainer);
    btnStart = new QPushButton("Start");
    btnStart->setFixedSize(AppConstants::BUTTON_WIDTH,
                           AppConstants::BUTTON_HEIGHT);
    btnOption = new QPushButton("Настройки");
    btnOption->setFixedSize(AppConstants::BUTTON_WIDTH,
                            AppConstants::BUTTON_HEIGHT);
    btnExit = new QPushButton("Exit");
    btnExit->setFixedSize(AppConstants::BUTTON_WIDTH,
                          AppConstants::BUTTON_HEIGHT);

    middleLayout->addWidget(btnStart, 0, Qt::AlignHCenter);
    middleLayout->addWidget(btnOption, 0, Qt::AlignHCenter);
    middleLayout->addWidget(btnExit, 0, Qt::AlignHCenter);

    mainLayout->addWidget(middleContainer);
}

void MainWidget::setupBottomPanel() {
    bottomContainer = new QWidget();
    QVBoxLayout *bottomLayout = new QVBoxLayout(bottomContainer);
    QLabel *statusLabel = new QLabel(AppConstants::DEVELOPER_INFO);
    statusLabel->setObjectName("statusLabel");

    bottomLayout->addWidget(statusLabel, 0, Qt::AlignHCenter);

    mainLayout->addWidget(bottomContainer);
}