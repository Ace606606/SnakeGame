// ./include/optionWidget.hpp

#pragma once
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class QSpinBox;
class QCheckBox;

namespace OptionConstants {
const int MIN_SPEED = 50;
const int MAX_SPEED = 1000;
const int DEFAULT_SPEED = 300;
}  // namespace OptionConstants

class OptionWidget : public QWidget {
    Q_OBJECT

   public:
    explicit OptionWidget(QWidget* parent = nullptr);

    int getSpeed() const;
    bool isWallCrossingAllowed() const;

   signals:
    void backToMenu();

   private:
    void setupSpeedControls(QVBoxLayout* layout);
    void setupWallCrossingControls(QVBoxLayout* layout);
    QSpinBox* speedBox;
    QCheckBox* wallCrossingBox;
    QPushButton* btnBack;
};