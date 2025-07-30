// ./include/option_widget.hpp

#pragma once

#include "base_page_widget.hpp"
#include "constants.hpp"

class QPushButton;
class QCheckBox;
class QComboBox;

class OptionWidget : public BasePageWidget {
    Q_OBJECT

   public:
    explicit OptionWidget(QWidget *parent = nullptr);
    ~OptionWidget() = default;

    virtual void retranslateUi() override;

    AppConstants::GameSettings::Difficulty getSelectedDifficulty() const;
    bool getIsWallCrossingAllowed() const;
    QString getSelectedLanguageCode() const;

    void loadSettings();
    void saveSettings();

   signals:
    void backToMainMenu();
    void settingsChangedAndSaved();
    void requestLanguageChange(const QString &languageCode);

   protected:
    void setupContentPanel() override;
    void setupConnections() override;

   private slots:
    void onDifficultyChanged(int index);
    void onWallCrossingChanged(bool checked);
    void onLanguageComboBoxChanged(int index);

    void onAboutClicked();
    void onBackToMainMenuClicked();
    void onSaveClicked();

   private:
    QLabel *m_difficultyLabel = nullptr;
    QComboBox *m_difficultyComboBox = nullptr;

    QLabel *m_wallCrossingLabel = nullptr;
    QCheckBox *m_wallCrossingCheckBox = nullptr;

    QLabel *m_languageLabel = nullptr;
    QComboBox *m_languageComboBox = nullptr;

    QPushButton *m_aboutButton = nullptr;
    QPushButton *m_backButton = nullptr;
    QPushButton *m_saveButton = nullptr;

    bool m_settingsChanged = false;
    void setupContentButtons(QVBoxLayout *contentLayout);
    void setupDifficultyControls(QVBoxLayout *layoutContentButtons);
    void setupWallCrossingControls(QVBoxLayout *layoutContentButtons);
    void setupLanguageControls(QVBoxLayout *layoutContentButtons);
    void setupActionButtons(QVBoxLayout *layoutContentButtons,
                            QWidget *contentButtons);
    void showUnsavedChangedDialog();
};