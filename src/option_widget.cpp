// ./src/optionWidget.cpp

#include "option_widget.hpp"

#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QVBoxLayout>

OptionWidget::OptionWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    setupSpeedControls(layout);
    setupWallCrossingControls(layout);
}

void OptionWidget::setupSpeedControls(QVBoxLayout* layout) {
    QLabel* descrSpeed = new QLabel("Скорость (мс на ход):");
    descrSpeed->setObjectName("descrSpeed");
    layout->addWidget(descrSpeed);

    speedBox = new QSpinBox();
    speedBox->setRange(OptionConstants::MIN_SPEED, OptionConstants::MAX_SPEED);
    speedBox->setValue(OptionConstants::DEFAULT_SPEED);
    layout->addWidget(speedBox);
}

void OptionWidget::setupWallCrossingControls(QVBoxLayout* layout) {
    wallCrossingBox = new QCheckBox("Разрешить проход сквозь стены");
    wallCrossingBox->setObjectName("wallCrossingBox");
    wallCrossingBox->setChecked(false);
    layout->addWidget(wallCrossingBox);
}

int OptionWidget::getSpeed() const { return speedBox->value(); }
bool OptionWidget::isWallCrossingAllowed() const {
    return wallCrossingBox->isChecked();
}