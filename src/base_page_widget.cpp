// ./src/base_page_widget.cpp

#include "base_page_widget.hpp"

#include <QEvent>
#include <QLabel>
#include <QVBoxLayout>

#include "constants.hpp"
#include "ui_factory.hpp"

BasePageWidget::BasePageWidget(QWidget* parent) : QWidget(parent) {
    setupBaseUI();
}

void BasePageWidget::setupBaseUI() {
    setObjectName("BasePageWidget");
    setAttribute(Qt::WA_StyledBackground, true);
    m_mainLayout = new QVBoxLayout(this);
    setupTopPanel();
    m_mainLayout->addWidget(m_topContainer, 2);
}

void BasePageWidget::setupTopPanel() {
    m_topContainer = new QWidget(this);
    m_topContainer->setObjectName("BasePageWidget_m_topContainer");
    QVBoxLayout* topLayout = new QVBoxLayout(m_topContainer);

    m_appTitleLabel = UiFactory::createTitleLabel(
        AppConstants::AboutApp::APP_NAME, m_topContainer,
        "BasePageWidget_m_appTitleLabel");
    topLayout->addWidget(m_appTitleLabel, 5);

    m_pageTitleLabel = UiFactory::createTitleLabel(
        "", m_topContainer, "BasePageWidget_m_pageTitleLabel");
    topLayout->addWidget(m_pageTitleLabel, 1);
}

void BasePageWidget::changeEvent(QEvent* event) {
    if (event->type() == QEvent::LanguageChange) {
        retranslateUi();
    }
    QWidget::changeEvent(event);
}
