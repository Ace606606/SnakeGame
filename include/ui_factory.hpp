// ./src/ui_factory.hpp
#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QWidget>

class UiFactory {
   public:
    static QPushButton* createStandardButton(
        const QString& text, QWidget* parent = nullptr,
        const QString& nameButton = "StandardButton");

    static QPushButton* createStandardButton(
        const QString& text, int width, int height, QWidget* parent = nullptr,
        const QString& nameButton = "StandardButton");

    static QComboBox* createStandardComboBox(
        QWidget* parent, const QString& nameCmbBox = "StdComboBox");

    static QCheckBox* createStandardCheckBox(
        const QString& text, QWidget* parent,
        const QString& nameChckBox = "StdCheckBox");

    static QLabel* createTitleLabel(const QString& text,
                                    QWidget* parent = nullptr,
                                    const QString& nameLabel = "TitleLabel");

    static QLabel* createInfoLabel(const QString& text,
                                   QWidget* parent = nullptr,
                                   const QString& nameLabel = "InfoLabel");
};