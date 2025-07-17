// ./include/mainWidget.hpp
#pragma once
#include <QPushButton>
#include <QWidget>

class QVBoxLayout;

class MainWidget : public QWidget {
    Q_OBJECT
   public:
    explicit MainWidget(QWidget* parent = nullptr);

   private:
    void setupMainWidget();
    void setupTopPanel();
    void setupMiddlePanel();
    void setupBottomPanel();

    QVBoxLayout* mainLayout;
    QWidget* topContainer;
    QWidget* middleContainer;
    QWidget* bottomContainer;

    // btn
    QPushButton* btnStart = nullptr;
    QPushButton* btnOption = nullptr;
    QPushButton* btnExit = nullptr;

   signals:
    void startGameClicked();
    void optionClicked();
    void exitClicked();
};