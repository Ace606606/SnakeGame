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
    bool isWallCrossingAllowed() const;
    QString getSelectedLanguageCode() const;

    void loadSettings();
    void saveSettings();

   signals:
    void backToMainMenu();
    void settingsChangeAndSaved();
    void requestLanguageChange(const QString &languageCode);
    void settingsChangedAndSaved();

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
    QLabel *m_difficultyLabel;
    QComboBox *m_difficultyComboBox;

    QLabel *m_wallCrossingLabel;
    QCheckBox *m_wallCrossingCheckBox;

    QLabel *m_languageLabel;
    QComboBox *m_languageComboBox;

    QPushButton *m_aboutButton;
    QPushButton *m_backButton;
    QPushButton *m_saveButton;

    bool m_settingsChanged = false;
    void setupContentButtons(QVBoxLayout *contentLayout);
    void setupDifficultyControls(QVBoxLayout *contentLayout);
    void setupWallCrossingControls(QVBoxLayout *contentLayout);
    void setupLanguageControls(QVBoxLayout *contentLayout);
    void setupActionButtons(QVBoxLayout *contentLayout);

    void showUnsavedChangedDialog();
    void applyLoadedSettings();
};