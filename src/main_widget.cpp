// ./src/main_widget.cpp

#include "main_widget.hpp"

#include <spdlog/spdlog.h>

#include <QPushButton>
#include <QVBoxLayout>

#include "constants.hpp"
#include "ui_factory.hpp"

MainWidget::MainWidget(QWidget *parent) : BasePageWidget(parent) {
    SPDLOG_DEBUG("Create MainMenu.");
    setupContentPanel();
    setupConnections();
}

void MainWidget::setupContentPanel() {
    if (m_pageTitleLabel) {
        m_pageTitleLabel->setText(tr("Main Menu"));
    }

    QWidget *m_contentContainer = new QWidget(this);
    m_contentContainer->setObjectName("MainWidget_w_m_contentContainer");
    m_contentContainer->setAttribute(Qt::WA_StyledBackground, true);
    QVBoxLayout *contentLayout = new QVBoxLayout(m_contentContainer);

    setupContentButtons(contentLayout);

    m_mainLayout->addWidget(m_contentContainer, 3);
}

void MainWidget::setupContentButtons(QVBoxLayout *contentLayout) {
    QWidget *contentButtons = new QWidget();
    contentButtons->setObjectName("MainWidget_contentButtons");
    QVBoxLayout *layoutContentButtons = new QVBoxLayout(contentButtons);
    layoutContentButtons->setSpacing(10);

    m_btnStart = UiFactory::createStandardButton(
        tr("Start"), AppConstants::BUTTON_WIDTH, AppConstants::BUTTON_HEIGHT,
        contentButtons, "MainWidget_btn_Start");
    m_btnOption = UiFactory::createStandardButton(
        tr("Options"), AppConstants::BUTTON_WIDTH, AppConstants::BUTTON_HEIGHT,
        contentButtons, "MainWidget_btn_Options");
    m_btnExit = UiFactory::createStandardButton(
        tr("Exit"), AppConstants::BUTTON_WIDTH, AppConstants::BUTTON_HEIGHT,
        contentButtons, "MainWidget_btn_Exit");

    layoutContentButtons->addWidget(m_btnStart, 0, Qt::AlignHCenter);
    layoutContentButtons->addWidget(m_btnOption, 0, Qt::AlignHCenter);
    layoutContentButtons->addWidget(m_btnExit, 0, Qt::AlignHCenter);

    contentLayout->addWidget(contentButtons, 0, Qt::AlignTop);
}

void MainWidget::setupConnections() {
    connect(m_btnStart, &QPushButton::clicked, this,
            &MainWidget::startGameClicked);
    connect(m_btnOption, &QPushButton::clicked, this,
            &MainWidget::optionClicked);
    connect(m_btnExit, &QPushButton::clicked, this, &MainWidget::exitClicked);
}

void MainWidget::retranslateUi() {
    SPDLOG_DEBUG("Change language main_menu.");
    if (m_pageTitleLabel) {
        m_pageTitleLabel->setText(tr("Main Menu"));
    }

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