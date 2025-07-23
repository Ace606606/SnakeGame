// ./include/main_widget.hpp
#pragma once

#include "base_page_widget.hpp"

class QVBoxLayout;
class QPushButton;

class MainWidget : public BasePageWidget {
    Q_OBJECT
   public:
    explicit MainWidget(QWidget* parent = nullptr);
    ~MainWidget() = default;

    void retranslateUi() override;

   protected:
    void setupContentPanel() override;
    void setupConnections() override;

   signals:
    void startGameClicked();
    void optionClicked();
    void exitClicked();

   private:
    void setupContentButtons(QVBoxLayout* contentLayout);
    QPushButton* m_btnStart = nullptr;
    QPushButton* m_btnOption = nullptr;
    QPushButton* m_btnExit = nullptr;
};