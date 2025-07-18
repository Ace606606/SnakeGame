// ./include/mainWidget.hpp
#pragma once
#include <QPushButton>
#include <QWidget>

class QVBoxLayout;

class MainWidget : public QWidget {
    Q_OBJECT
   public:
    explicit MainWidget(QWidget* parent = nullptr);
    ~MainWidget() = default;

    void retranslateUi();

   protected:
    void changeEvent(QEvent* event) override;
   signals:
    void startGameClicked();
    void optionClicked();
    void exitClicked();

   private:
    QVBoxLayout* m_mainLayout;
    QWidget* m_topContainer;
    QWidget* m_middleContainer;
    // btn
    QPushButton* m_btnStart = nullptr;
    QPushButton* m_btnOption = nullptr;
    QPushButton* m_btnExit = nullptr;

    void setupUi();
    void setupConnections();
    void setupTopPanel();
    void setupMiddlePanel();
    void setupBottomPanel();
};