// ./include/base_page_widget.hpp

#pragma once

#include <QWidget>

class QLabel;
class QVBoxLayout;
class QEvent;

class BasePageWidget : public QWidget {
    Q_OBJECT

   public:
    explicit BasePageWidget(QWidget *parent = nullptr);
    virtual ~BasePageWidget() = default;

    virtual void retranslateUi() = 0;

   protected:
    QVBoxLayout *m_mainLayout;
    QWidget *m_topContainer;

    QLabel *m_appTitleLabel;
    QLabel *m_pageTitleLabel;

    void setupBaseUI();
    virtual void setupTopPanel();
    virtual void setupContentPanel() = 0;
    virtual void setupConnections() = 0;

    void changeEvent(QEvent *event) override;
};