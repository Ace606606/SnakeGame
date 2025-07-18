// ./src/mainWidget.cpp

#include "main_widget.hpp"

#include <QEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "constants.hpp"
#include "ui_factory.hpp"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    setupUi();
    setupConnections();
    retranslateUi();
}

void MainWidget::setupConnections() {
    connect(m_btnStart, &QPushButton::clicked, this,
            &MainWidget::startGameClicked);
    connect(m_btnOption, &QPushButton::clicked, this,
            &MainWidget::optionClicked);
    connect(m_btnExit, &QPushButton::clicked, this, &MainWidget::exitClicked);
}

void MainWidget::setupTopPanel() {
    m_topContainer = new QWidget(this);
    QVBoxLayout *topLayout = new QVBoxLayout(m_topContainer);

    QLabel *titleLabel =
        UiFactory::createTitleLabel(AppConstants::WINDOW_TITLE);
    topLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
}

void MainWidget::setupMiddlePanel() {
    m_middleContainer = new QWidget(this);
    QVBoxLayout *middleLayout = new QVBoxLayout(m_middleContainer);

    m_btnStart = UiFactory::createStandardButton(
        tr("Start"), AppConstants::BUTTON_WIDTH, AppConstants::BUTTON_HEIGHT,
        m_middleContainer);
    m_btnOption = UiFactory::createStandardButton(
        tr("Options"), AppConstants::BUTTON_WIDTH, AppConstants::BUTTON_HEIGHT,
        m_middleContainer);
    m_btnExit = UiFactory::createStandardButton(
        tr("Exit"), AppConstants::BUTTON_WIDTH, AppConstants::BUTTON_HEIGHT,
        m_middleContainer);

    middleLayout->addWidget(m_btnStart, 0, Qt::AlignHCenter);
    middleLayout->addWidget(m_btnOption, 0, Qt::AlignHCenter);
    middleLayout->addWidget(m_btnExit, 0, Qt::AlignHCenter);
}

void MainWidget::setupUi() {
    m_mainLayout = new QVBoxLayout(this);
    setupTopPanel();
    setupMiddlePanel();
    m_mainLayout->addStretch(2);
    m_mainLayout->addWidget(m_topContainer);

    m_mainLayout->addWidget(m_middleContainer);
    m_mainLayout->addStretch(3);
}

void MainWidget::retranslateUi() {
    if (m_btnStart) {
        m_btnStart->setText(tr("Start"));
    }
    if (m_btnOption) {
        m_btnOption->setText(tr("Options"));
    }
    if (m_btnExit) {
        m_btnExit->setText(tr("Exit"));
    }
}

void MainWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        retranslateUi();
    }
    QWidget::changeEvent(event);
}