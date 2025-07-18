// ./srs/ui_factory.hpp
#pragma once

#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QWidget>

class UiFactory {
   public:
    static QPushButton* createStandardButton(const QString& text,
                                             QWidget* parent = nullptr);
    static QPushButton* createStandardButton(const QString& text, int width,
                                             int height,
                                             QWidget* parent = nullptr);

    static QLabel* createTitleLabel(const QString& text,
                                    QWidget* parent = nullptr);
    static QLabel* createInfoLabel(const QString& text,
                                   QWidget* parent = nullptr);

    static QWidget* createTopPanel(const QString& titleText);
    static QWidget* createMiddlePanel();
    static QWidget* createBottomPanel(const QString& titleText);
};