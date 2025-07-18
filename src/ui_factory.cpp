// ./srs/ui_factory.cpp
#include "ui_factory.hpp"

QPushButton* UiFactory::createStandardButton(const QString& text,
                                             QWidget* parent) {
    QPushButton* button = new QPushButton(text, parent);
    return button;
}

QPushButton* UiFactory::createStandardButton(const QString& text, int width,
                                             int height, QWidget* parent) {
    QPushButton* button = new QPushButton(text, parent);
    button->setFixedSize(width, height);
    return button;
}

QLabel* UiFactory::createTitleLabel(const QString& text, QWidget* parent) {
    QLabel* label = new QLabel(text, parent);
    label->setAlignment(Qt::AlignHCenter);
    label->setObjectName("TitleLabel");
    return label;
}

QLabel* UiFactory::createInfoLabel(const QString& text, QWidget* parent) {
    QLabel* label = new QLabel(text, parent);
    label->setObjectName("InfoLabel");
    return label;
}