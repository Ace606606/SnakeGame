// ./src/option_widget.cpp

#include "option_widget.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QDesktopServices>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QUrl>

#include "constants.hpp"
#include "language_manager.hpp"
#include "ui_factory.hpp"

OptionWidget::OptionWidget(QWidget* parent) : BasePageWidget(parent) {
    setupContentPanel();
    setupConnections();

    loadSettings();
    applyLoadedSettings();
}

void OptionWidget::setupContentPanel() {
    if (m_pageTitleLabel) {
        m_pageTitleLabel->setText(tr("Option"));
    }

    QWidget* m_contentContainer = new QWidget(this);
    m_contentContainer->setObjectName("OptionWidget_m_contentContainer");
    QVBoxLayout* contentLayout = new QVBoxLayout(m_contentContainer);

    setupContentButtons(contentLayout);

    m_mainLayout->addWidget(m_contentContainer, 3);
}

void OptionWidget::setupContentButtons(QVBoxLayout* contentLayout) {
    QWidget* contentButtons = new QWidget();
    contentButtons->setObjectName("OptionWidget_contentButtons");
    QVBoxLayout* layoutContentButtons = new QVBoxLayout(contentButtons);
    layoutContentButtons->setSpacing(10);

    setupLanguageControls(layoutContentButtons);
    setupDifficultyControls(layoutContentButtons);
    setupWallCrossingControls(layoutContentButtons);
    setupActionButtons(layoutContentButtons);

    contentLayout->addWidget(contentButtons, 0,
                             Qt::AlignHCenter | Qt::AlignTop);
}

void OptionWidget::setupLanguageControls(QVBoxLayout* contentLayout) {
    QHBoxLayout* hLayout = new QHBoxLayout();
    m_languageLabel = UiFactory::createInfoLabel(
        tr("Language:"), this, "OptionWidget_m_languageLabel");
    m_languageComboBox = UiFactory::createStandardComboBox(
        this, "OptionWidget_m_languageComboBox");

    for (const QString& langCode :
         LanguageManager::instance().availableLanguages()) {
        m_languageComboBox->addItem(
            AppConstants::LanguageCodes::LANGUAGE_NAMES.value(langCode,
                                                              langCode),
            langCode);
    }

    QString currentLangCode = LanguageManager::instance().currentLanguage();
    if (currentLangCode.isEmpty()) {
        currentLangCode = AppConstants::LanguageCodes::DEFAULT_LANGUAGE;
    }

    int currentIndex = m_languageComboBox->findData(currentLangCode);
    if (currentIndex != -1) {
        m_languageComboBox->setCurrentIndex(currentIndex);
    }

    hLayout->addWidget(m_languageLabel);
    hLayout->addWidget(m_languageComboBox);

    contentLayout->addLayout(hLayout);
}

void OptionWidget::setupDifficultyControls(QVBoxLayout* contentLayout) {
    QHBoxLayout* hLayout = new QHBoxLayout();
    m_difficultyLabel = UiFactory::createInfoLabel(
        tr("Difficulty"), this, "OptionWidget_m_difficultyLabel");
    m_difficultyComboBox = UiFactory::createStandardComboBox(
        this, "OptionWidget_m_difficultyComboBox");

    m_difficultyComboBox->addItem(
        tr("Easy"),
        QVariant::fromValue(AppConstants::GameSettings::Difficulty::Easy));
    m_difficultyComboBox->addItem(
        tr("Medium"),
        QVariant::fromValue(AppConstants::GameSettings::Difficulty::Medium));
    m_difficultyComboBox->addItem(
        tr("Hard"),
        QVariant::fromValue(AppConstants::GameSettings::Difficulty::Hard));

    int defaultIndex = 0;
    for (int i = 0; i < m_difficultyComboBox->count(); ++i) {
        if (m_difficultyComboBox->itemData(i)
                .value<AppConstants::GameSettings::Difficulty>() ==
            AppConstants::GameSettings::DEFAULT_DIFFICULTY) {
            defaultIndex = i;
            break;
        }
    }

    m_difficultyComboBox->setCurrentIndex(defaultIndex);

    hLayout->addWidget(m_difficultyLabel);
    hLayout->addWidget(m_difficultyComboBox);
    contentLayout->addLayout(hLayout);
}

void OptionWidget::setupWallCrossingControls(QVBoxLayout* contentLayout) {
    m_wallCrossingCheckBox = UiFactory::createStandardCheckBox(
        tr("Allow wall crossing"), this, "OptionWidget_m_wallCrossingCheckBox");
    m_wallCrossingCheckBox->setChecked(
        AppConstants::GameSettings::DEFAULT_WALL_CROSSING);
    contentLayout->addWidget(m_wallCrossingCheckBox);
}

void OptionWidget::setupActionButtons(QVBoxLayout* contentLayout) {
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    m_aboutButton = UiFactory::createStandardButton(
        tr("About"), AppConstants::BUTTON_WIDTH, AppConstants::BUTTON_HEIGHT,
        this, "OptionWidget_m_aboutButton");
    m_backButton = UiFactory::createStandardButton(
        tr("Back to Main Menu"), AppConstants::BUTTON_WIDTH,
        AppConstants::BUTTON_HEIGHT, this, "OptionWidget_m_backButton");

    m_saveButton = UiFactory::createStandardButton(
        tr("Save"), AppConstants::BUTTON_WIDTH, AppConstants::BUTTON_HEIGHT,
        this, "OptionWidget_m_aboutButton");
    buttonLayout->addWidget(m_aboutButton);
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_backButton);

    contentLayout->addLayout(buttonLayout);
}

void OptionWidget::setupConnections() {
    connect(m_difficultyComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &OptionWidget::onDifficultyChanged);

    connect(m_wallCrossingCheckBox, &QCheckBox::clicked, this,
            &OptionWidget::onWallCrossingChanged);

    connect(m_languageComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &OptionWidget::onLanguageComboBoxChanged);

    connect(m_aboutButton, &QPushButton::clicked, this,
            &OptionWidget::onAboutClicked);
    connect(m_backButton, &QPushButton::clicked, this,
            &OptionWidget::onBackToMainMenuClicked);
    connect(m_saveButton, &QPushButton::clicked, this,
            &OptionWidget::onSaveClicked);
}

void OptionWidget::retranslateUi() {
    if (m_pageTitleLabel) {
        m_pageTitleLabel->setText(tr("Option"));
    }

    if (m_difficultyLabel) m_difficultyLabel->setText(tr("Difficulty"));

    if (m_difficultyComboBox) {
        m_difficultyComboBox->setItemText(
            m_difficultyComboBox->findData(QVariant::fromValue(
                AppConstants::GameSettings::Difficulty::Easy)),
            tr("Easy"));

        m_difficultyComboBox->setItemText(
            m_difficultyComboBox->findData(QVariant::fromValue(
                AppConstants::GameSettings::Difficulty::Medium)),
            tr("Medium"));

        m_difficultyComboBox->setItemText(
            m_difficultyComboBox->findData(QVariant::fromValue(
                AppConstants::GameSettings::Difficulty::Hard)),
            tr("Hard"));
    }

    if (m_wallCrossingCheckBox)
        m_wallCrossingCheckBox->setText(tr("Allow wall crossing"));

    if (m_languageLabel) m_languageLabel->setText(tr("Language"));

    if (m_languageComboBox) {
        for (int i = 0; i < m_languageComboBox->count(); ++i) {
            QString langCode = m_languageComboBox->itemData(i).toString();
            m_languageComboBox->setItemText(
                i, AppConstants::LanguageCodes::LANGUAGE_NAMES.value(langCode,
                                                                     langCode));
        }
    }

    if (m_aboutButton) m_aboutButton->setText(tr("About"));
    if (m_backButton) m_backButton->setText(tr("Back to Main Menu"));
    if (m_saveButton) m_saveButton->setText(tr("Save"));
}

void OptionWidget::onDifficultyChanged(int index) {
    Q_UNUSED(index);
    m_settingsChanged = true;
}

void OptionWidget::onWallCrossingChanged(bool checked) {
    Q_UNUSED(checked);
    m_settingsChanged = true;
}

void OptionWidget::onLanguageComboBoxChanged(int index) {
    Q_UNUSED(index);
    m_settingsChanged = true;
}

void OptionWidget::onAboutClicked() {
    QMessageBox aboutBox(this);
    aboutBox.setObjectName("OptionWidget_aboutBox");
    aboutBox.setWindowTitle(tr("About Snake Game"));
    aboutBox.setText(tr("<h3>%1</h3>"
                        "<p>Version: %2</p>"
                        "<p>Developer: %3</p>"
                        "<p>GitHub: <a href=\"%4\">%4</a></p>")
                         .arg(AppConstants::AboutApp::APP_NAME)
                         .arg(AppConstants::AboutApp::VERSION)
                         .arg(AppConstants::AboutApp::DEVELOPER)
                         .arg(AppConstants::AboutApp::GITHUB_LINK));

    aboutBox.setTextFormat(Qt::RichText);
    aboutBox.setTextInteractionFlags(Qt::TextBrowserInteraction);

    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.exec();
}

void OptionWidget::onBackToMainMenuClicked() {
    if (m_settingsChanged) {
        showUnsavedChangedDialog();
    } else {
        emit backToMainMenu();
    }
}

void OptionWidget::onSaveClicked() {
    saveSettings();
    m_settingsChanged = false;
    emit settingsChangedAndSaved();
}

AppConstants::GameSettings::Difficulty OptionWidget::getSelectedDifficulty()
    const {
    return m_difficultyComboBox->currentData()
        .value<AppConstants::GameSettings::Difficulty>();
}

bool OptionWidget::isWallCrossingAllowed() const {
    return m_wallCrossingCheckBox->isChecked();
}

QString OptionWidget::getSelectedLanguageCode() const {
    return m_languageComboBox->currentData().toString();
}

void OptionWidget::loadSettings() {
    qDebug() << "OptionWidget: Loading settings...";
    m_settingsChanged = false;
}

void OptionWidget::saveSettings() {
    qDebug() << "OptionWidget: Saving settings:";
    qDebug() << "  Difficulty:"
             << AppConstants::GameSettings::DIFFICULTY_NAMES.value(
                    getSelectedDifficulty());
    qDebug() << "  Speed:"
             << AppConstants::GameSettings::DIFFICULTY_SPEEDS.value(
                    getSelectedDifficulty())
             << "ms";
    qDebug() << "  Wall Crossing:" << isWallCrossingAllowed();
    qDebug() << "  Language:" << getSelectedLanguageCode();
}

void OptionWidget::showUnsavedChangedDialog() {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Unsaved Changes"));
    msgBox.setText(tr(
        "You have unsaved changes. Do you want to save them before exiting?"));
    msgBox.setInformativeText(
        tr("Your changes will be lost if you don't save."));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                              QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Save:
            onSaveClicked();
            emit backToMainMenu();
            break;
        case QMessageBox::Discard:
            emit backToMainMenu();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}

void OptionWidget::applyLoadedSettings() {
    int defaultDifficultyIndex = m_difficultyComboBox->findData(
        QVariant::fromValue(AppConstants::GameSettings::DEFAULT_DIFFICULTY));
    if (defaultDifficultyIndex != -1) {
        m_difficultyComboBox->setCurrentIndex(defaultDifficultyIndex);
    }

    m_wallCrossingCheckBox->setChecked(
        AppConstants::GameSettings::DEFAULT_WALL_CROSSING);

    QString currentLangCode = LanguageManager::instance().currentLanguage();
    if (currentLangCode.isEmpty()) {
        currentLangCode = AppConstants::LanguageCodes::DEFAULT_LANGUAGE;
    }

    int currentLanguageIndex = m_languageComboBox->findData(currentLangCode);
    if (currentLanguageIndex != -1) {
        m_languageComboBox->setCurrentIndex(currentLanguageIndex);
    }

    m_settingsChanged = false;
}