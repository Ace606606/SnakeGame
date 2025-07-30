// ./src/ui_factory.cpp
#include "ui_factory.hpp"

QPushButton* UiFactory::createStandardButton(const QString& text,
                                             QWidget* parent,
                                             const QString& nameButton) {
    QPushButton* button = new QPushButton(text, parent);
    button->setObjectName(nameButton);
    return button;
}

QPushButton* UiFactory::createStandardButton(const QString& text, int width,
                                             int height, QWidget* parent,
                                             const QString& nameButton) {
    QPushButton* button = new QPushButton(text, parent);
    button->setFixedSize(width, height);
    button->setObjectName(nameButton);
    return button;
}

QComboBox* UiFactory::createStandardComboBox(QWidget* parent,
                                             const QString& nameComboBox) {
    QComboBox* comboBox = new QComboBox(parent);
    comboBox->setObjectName(nameComboBox);
    return comboBox;
}

QCheckBox* UiFactory::createStandardCheckBox(const QString& text,
                                             QWidget* parent,
                                             const QString& nameChckBox) {
    QCheckBox* сheckBox = new QCheckBox(text, parent);
    сheckBox->setObjectName(nameChckBox);
    return сheckBox;
}

QLabel* UiFactory::createTitleLabel(const QString& text, QWidget* parent,
                                    const QString& nameLabel) {
    QLabel* label = new QLabel(text, parent);
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName(nameLabel);
    return label;
}

QLabel* UiFactory::createInfoLabel(const QString& text, QWidget* parent,
                                   const QString& nameLabel) {
    QLabel* label = new QLabel(text, parent);
    label->setObjectName(nameLabel);
    return label;
}